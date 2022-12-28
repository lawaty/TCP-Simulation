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

#define MAX_QUEUE 5

using namespace std;

void handleConnection(int sock)
{
  Connection conn(sock);
  vector<string> splitted = split(conn.recv());

  if(splitted[0] == "GET")
    conn.echo(handleGet(splitted[1]));

  else if(splitted[0] == "POST")
    conn.echo(handlePost(splitted[1], conn));
}

class Server
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
  bool running;

public:
  /**
   * Method prepares the required data structures for operating the server
   * @param char[] ip
   * @param char[] port
   */
  Server(char *ip, char *port);
  /**
   * Method initializes listeners and manager connection requests
   */
  void start();
  /**
   * Method stops listeners
   */
  void stop();
};

Server::Server(char *ip, char *port) // initializing the server
{
  address = new AddrInfo(ip, port);

  cout << "Initialized server successfully with ip: " << address->getIP() << " and port " << address->getPort() << endl;
}

void Server::start()
{
  // Starting listener

  sock = socket(AF_INET, SOCK_DGRAM, 0);
  if (sock == -1)
    Output::showError("socket");

  if (bind(sock, address->format(), address->getLength()) == -1)
    Output::showError("bind");

  if (listen(sock, MAX_QUEUE) == -1)
    Output::showError("listen");

  // Accepting Connections
  struct sockaddr_storage their_addr; // connector address
  running = true;

  Output::showSuccess("Listening...");

  while (running)
  {
    socklen_t size = sizeof(their_addr);
    int conn_id = accept(sock, (struct sockaddr *)&their_addr, &size);

    // Connection rejected
    if (conn_id == -1)
    {
      Output::showError("Initializing communication with client failed", false);
      continue;
    }

    // Connection accepted
    Output::showSuccess("Connection Accepted");

    int id = fork();

    if (!id) // Child process
      handleConnection(conn_id);

    else
      close(id); // Parent doesn't need the connection descriptor at all
  }
}

void Server::stop()
{
  close(sock);
  cout << "Server closed";
  running = false;
}
