#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

#define CHANNEL

#ifndef OUTPUT
#include "Output.h"
#endif

#define MSS 508
#define ACK_SIZE 8
#define CONTENT_SIZE 500

struct DPacket
{
  uint16_t cksum = 0;
  uint16_t len;
  uint32_t seqno;

  char data[CONTENT_SIZE + 1];
};

struct AckPacket
{
  uint16_t cksum = 0;
  uint16_t len;
  uint32_t ackno;
};

/**
 * Easier the communication functions by providing simple echo and recv methods
 */
class Channel
{
private:
  int sock;
  Address *dist;

public:
  /**
   * Channel instance initializer
   */
  Channel(int sock, Address *dist);
  void echo(char *msg);
  void echoString(string msg);
  char *recv();

  template <typename PacketType>
  void sendPacket(PacketType pack);
  void recvPacket();
};

Channel::Channel(int sock, Address *dist)
{
  this->sock = sock;
  this->dist = dist;
}

void Channel::echo(char *msg)
{
  ssize_t len = sendto(sock, msg, strlen(msg), 0, dist->format(), sizeof(struct sockaddr));
  if (len == -1)
    Output::showError("sendto");
    
  cout << "Sent: " << msg << endl;
}

void Channel::echoString(string msg)
{
  char *p = &msg[0];
  echo(p);
};

char *Channel::recv()
{
  socklen_t addrlen = sizeof(struct sockaddr);
  char *buf = new char[MSS];
  ssize_t num_bytes = recvfrom(sock, buf, MSS, 0, dist->format(), &addrlen);

  if (num_bytes == -1)
    Output::showError("recvfrom");

  return buf;
}

template <typename PacketType>
void Channel::sendPacket(PacketType pack)
{
  char *buffer = new char[MSS];
  memset(buffer, 0, MSS);
  memcpy(buffer, &pack, sizeof(pack));
  cout << buffer;
  echo(buffer);
}

void Channel::recvPacket()
{
  char *buf = recv();
  if (sizeof(buf) == 8)
    struct AckPacket pack;
  else
    struct DPacket pack;

  cout << buf;
}