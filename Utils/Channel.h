#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

#define CHANNEL

#ifndef OUTPUT
#include "Output.h"
#endif

#define MAX_SIZE 500000

/**
 * Entity easier the communication processes
*/
class Channel
{
private:
  int sock;
  Address dist;
  char buf[MAX_SIZE];

public:
  Channel();
  Channel(int id);

  void echo(string msg);
  char* recv();
};

Channel::Channel(int sock, char filename[])
{
  this->sock = sock;
  this->filename = filename;
  if(!file_exists(String(filename))){
    Output::showError("File Not Found");
    this->echo("Not Found");
  }
}

void Channel::echo(string msg){
  char* p = &msg[0];
  int len = send(sock, p, strlen(p), 0);
  if(len > 0)
    cout << "Sent a msg with length " << len << endl;
  else
    Output::showError("send");

};

char* Channel::recv(){
  ssize_t num_bytes = recvfrom(src, buf, MAX_SIZE - 1, 0, dist->format(), dist->getLength());

  if(num_bytes == -1)
    Output::showError("recvfrom");

  return buf;
}