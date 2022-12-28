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

#ifndef ADDRINFO
#include "../Utils/AddrInfo.h"
#endif

#ifndef CONNECTION
#include "../Utils/Connection.h"
#endif

class Client
{
private:
  /**
   * DTO holds server info and provides easy interface to extract data from it
   */
  AddrInfo *address; // struct holding server info
  /**
   * Socket file descriptor
   */
  int sock;
  Connection *conn;

public:
  /**
   * Method prepares the required data structures for operating the server
   * @param char* ip
   * @param char* port
   */
  Client(char *ip, char *port);

  void upload(string path);

  void sendRequest(string msg);
};

Client::Client(char *ip, char *port)
{
  address = new AddrInfo(ip, port);

  sock = socket(AF_INET, SOCK_DGRAM, 0);
  if (sock == -1)
    Output::showError("socket");

  if (connect(sock, address->format(), address->getLength()) < 0)
    Output::showError("connect");

  Output::showSuccess("Connected successfully");

  conn = new Connection(sock);
}

void Client::upload(string path) {
  conn->echo("POST " + path);

  conn->recv();

  string line;
	ifstream s;
	s.open(path);

  string file_content; 
	while(getline(s, line))
		file_content += line + "\n";

  cout << file_content << endl;

  conn->echo(file_content);
  Output::showSuccess("Sent File Successfully");

}

void Client::sendRequest(string msg)
{
  conn->echo(msg);
  string buffer = string(conn->recv());

  int index = buffer.find("\n\n");
  string content = buffer.substr(index+1, buffer.length() - index);

  string path = msg.substr(4, msg.length() - 4);

  saveFile(path, content);
}