#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>

#define ADDR_INFO

/**
 * DTO for clarity
 */
class AddrInfo
{
public:
  struct sockaddr_in address;

  AddrInfo(char* ip, char* port)
  {
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = ip != NULL ? inet_addr(ip): INADDR_ANY;
    address.sin_port = htons(atoi(port));
    memset(address.sin_zero, '\0', sizeof address.sin_zero);
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