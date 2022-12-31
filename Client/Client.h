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

#ifndef Address
#include "../Utils/Address.h"
#endif

#ifndef CONNECTION
#include "../Utils/Channel.h"
#endif

class Client
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
  Channel *channel;

public:
  /**
   * Method prepares the required data structures for operating the server
   * @param char* ip
   * @param char* port
   */
  Client(char *ip, char *port);

  void requestFile(string filename);
};

Client::Client(char *ip, char *port)
{
  address = new Address(ip, port);

  sock = socket(AF_INET, SOCK_DGRAM, 0);
  if (sock == -1)
    Output::showError("socket");

  Output::showSuccess("Connected successfully");

  Address *dist = new Address(ip, port);
  channel = new Channel(sock, dist);
}

void Client::requestFile(string filename)
{
  channel->echoString(filename);

  // Packet *pack = channel->recvPacket();
  channel->recvPacket();
}