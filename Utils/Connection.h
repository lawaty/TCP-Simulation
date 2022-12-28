#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

#define CONNECTION

#ifndef OUTPUT
#include "Output.h"
#endif

#define MAX_SIZE 500000

/**
 * Entity easier the communication processes
*/
class Connection
{
private:
  int sock;
  char buf[MAX_SIZE];

public:
  Connection();
  Connection(int id);
  void handle();
  void echo(string msg);
  char* recv();
};

Connection::Connection(){}

Connection::Connection(int id)
{
  sock = id;
}

void Connection::echo(string msg){
  char* p = &msg[0];
  int len = send(sock, p, strlen(p), 0);
  if(len > 0)
    cout << "Sent a msg with length " << len << endl;
  else
    Output::showError("send");

};

char* Connection::recv(){

  long long num_bytes = read(sock, buf, MAX_SIZE - 1);
  if(num_bytes == -1)
    Output::showError("read");

  return buf;
}