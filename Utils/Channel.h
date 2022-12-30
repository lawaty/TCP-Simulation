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
  Address dist;

  uint16_t seq_num = 0;

  void echo(char* msg);
  void echo(string msg);
  char* recv();

public:
  /**
   * Channel instance initializer
  */
  Channel(int sock);
  void sendPacket(Packet pack);
  Packet recvPacket();
};

Channel::Channel(int sock)
{
  this->sock = sock;
}

void Channel::echo(char* msg)
{
  int len = send(sock, p, strlen(p), 0);
  if (len > 0)
    cout << "Sent a msg with length " << len << endl;
  else
    Output::showError("send");
}

void Channel::echo(string msg)
{
  char* p = &msg[0];
  echo(p);
};

char* Channel::recv()
{
  char buf[MSS];
  ssize_t num_bytes = recvfrom(src, buf, MAX_SIZE - 1, 0, dist->format(), dist->getLength());

  if (num_bytes == -1)
    Output::showError("recvfrom");

  return buf;
}

void Channel::sendPacket(template <typename Packet> pack)
{
  char* buffer = new char[MSS];
  memset(buffer, 0, MSS);
  memcpy(buffer, &pack, sizeof(pack));
  echo(buffer);
}

template <typename Packet> Channel::recvPacket()
{
  char* buf = recv();
  if(sizeof(buf) == 8)
    struct AckPacket pack;
  else
    struct DPacket pack;

  pack.seqno = seqNum;
  pack.len = string(buf).size();
}