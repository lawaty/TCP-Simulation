#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>

#define ADDRESS

/**
 * DTO for clarity
 */
class Address
{
public:
  struct sockaddr_in address;

  Address() {
    memset(&address, 0, sizeof(address));
  }

  Address(char* ip, char* port)
  {
    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = ip != NULL ? inet_addr(ip): INADDR_ANY;
    address.sin_port = htons(atoi(port));
  }

  struct sockaddr* format() {
    return (struct sockaddr* ) &address;
  }

  int getLength() {
    return sizeof(address);
  }

  char* getIP() {
    return inet_ntoa(address.sin_addr);
  }

  int getPort()
  {
    return htons(address.sin_port);
  }
};