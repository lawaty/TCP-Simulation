#include <string>
#include <vector>

#include <cstring>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

#ifndef OUTPUT
#include "../Utils/Output.h"
#endif

#ifndef ADDRESS
#include "../Utils/Address.h"
#endif

#ifndef CHANNEL
#include "../Utils/Channel.h"
#endif

#define MAX_QUERY_SIZE 100

using namespace std;

class Server
{
private:
  /**
   * DTO holds server info and provides easy interface to extract data from it
   */
  Address *address; // struct holding server info
  /**
   * Socket file descriptor
   */
  int sock;
  bool running;

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
};

Server::Server(char *ip, char *port) // initializing the server
{
  address = new Address(ip, port);

  cout << "Initialized server successfully with ip: " << address->getIP() << " and port " << address->getPort() << endl;
}

void Server::listen()
{
  char filename[MAX_QUERY_SIZE];
  ssize_t num_bytes = recvfrom(src, buf, MAX_QUERY_SIZE - 1, 0, dist->format(), dist->getLength());

  if (num_bytes < 1)
    Output::showError("Weird query");

  int conn_id = socket(AF_INET, SOCK_DGRAM, 0);

  if (conn_id == -1)
    Output::showError("Error Establishing Connection With Client");

  int pid = fork();
  if (!id)
  {
    new Channel(conn_id, filename);
    // Channel accepted
    Output::showSuccess("Channel Accepted");
  }

  else
    close(pid); // Parent doesn't need the connection descriptor at all
}

void Server::start()
{
  sock = socket(AF_INET, SOCK_DGRAM, 0);
  if (sock == -1)
    Output::showError("socket");

  if (bind(sock, address->format(), address->getLength()) == -1)
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
