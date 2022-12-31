#include "../Utils/File.h"

#ifndef OUTPUT
#include "../Utils/Output.h"
#endif

#ifndef ADDRESS
#include "../Utils/Address.h"
#endif

#ifndef CHANNEL
#include "../Utils/Channel.h"
#endif

#include "strategies/Strategy.h"

#define MSS 508
#define MAX_QUERY_SIZE 100

using namespace std;

typedef struct
{
  int start;
  int end;
} Window;

typedef struct
{
  struct DPacket *packet;
  chrono::time_point<chrono::system_clock> inst;

} TrackedPacket;

class Server
{
private:
  Address *address; // DTO holds server info
  int sock;         // Socket file descriptor
  bool running;     // flag

  // Congestion control
  State *state;
  Strategy *strategy;

public:
  /**
   * Method prepares the required data structures for operating the server
   * @param char[] ip
   * @param char[] port
   */
  Server(char *ip, char *port);

  /**
   * Method Listens for incoming connections
   */
  void listen();
  /**
   * Method initializes and manages connection requests
   */
  void start();
  /**
   * Method stops listeners
   */
  void stop();
  /**
   * Method sends file through reliable UDP socket
   */
  void sendFile(char filename[], int conn_id, Address *dist);
};

Server::Server(char *ip, char *port) // initializing the server
{
  address = new Address(ip, port);

  cout << "Initialized server successfully with ip: " << address->getIP() << " and port " << address->getPort() << endl;
}

void Server::listen()
{
  char filename[MAX_QUERY_SIZE];
  Address *dist;
  socklen_t addrlen = sizeof(struct sockaddr);

  while(true) {
    ssize_t num_bytes = recvfrom(sock, filename, MAX_QUERY_SIZE - 1, 0, dist->format(), &addrlen);
    
    if (num_bytes <= 0){
      cout << "Weird Query: " << filename << endl;
      continue;
    }

    int conn_id = socket(AF_INET, SOCK_DGRAM, 0);

    if (conn_id == -1)
      Output::showError("Error Establishing Connection With Client");

    int pid = fork();
    if (!pid)
    {
      Output::showSuccess("Channel Accepted");

      Server::sendFile(filename, conn_id, dist);
    }

    else
      close(pid); // Parent doesn't need the connection descriptor at all
  }
}

void Server::start()
{
  sock = socket(AF_INET, SOCK_DGRAM, 0);
  if (sock == -1)
    Output::showError("socket");

  struct sockaddr_in servaddr, cliaddr;

  // Bind the socket with the server address
  if (bind(sock, address->format(), address->getLength()) < 0)
    Output::showError("bind");

  // Accepting Channels
  running = true;
  Output::showSuccess("Listening...");
  while (running)
    listen();
}

void Server::stop()
{
  close(sock);
  cout << "Server closed";
  running = false;
}

void Server::sendFile(char filename[], int conn_id, Address *dist)
{
  Channel *channel = new Channel(conn_id, dist);

  // File Not Found
  File file(filename);
  if (!file.exists())
  {
    channel->echoString("404");
    Output::showError("File Not Found");
  }
  int chunks_count = ceil(file.getSize() / CONTENT_SIZE); // total number of chunks

  // Sending File Ack Packet
  struct AckPacket pack;
  pack.len = chunks_count;
  pack.ackno = 0;
  channel->sendPacket(pack);

  // state = new State();
  // strategy = SlowStart::getInst();
  // strategy->init(state);

  // Sending File Chunks
  Window window;
  window.start = 0;
  window.end = state->cwnd;

  vector<TrackedPacket *> on_flight;

  // Selective Repeat
  for (int i = window.start; i < window.end; i++)
  { // sending window packets
    struct DPacket *pack;
    string chunk = file.read(CONTENT_SIZE);

    strcpy(pack->data, chunk.c_str());
    pack->len = chunk.size();
    if (i == window.start)
      pack->seqno = 1;
    else
      pack->seqno = on_flight[i - 1]->packet->seqno + on_flight[i - 1]->packet->len;

    channel->sendPacket(&pack);

    TrackedPacket tracked_pack;
    tracked_pack.packet = pack;
    tracked_pack.inst = chrono::system_clock::now();
    on_flight.push_back(&tracked_pack);
  }

  // Receiving Acks
  for (int i = window.start; i < window.end; i++)
  {
    // AckPacket *pack = channel->recvPacket();
    channel->recvPacket();

    // // Remove it from tracked
    // for(auto *tracked : on_flight){
    //   if(tracked->packet->seqno == pack->ackno){
    //     on_flight.erase(on_flight.begin() + j);
    //     break;
    //   }
    // }

    // // Update state
    // strategy->newAck(state);
  }
}