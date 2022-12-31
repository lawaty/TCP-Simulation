#include <string>
#include <vector>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <algorithm>
#include <fstream>
#include <sstream>


#ifndef OUTPUT
#include "../Utils/Output.h"
#endif

#include "Client.h"

using namespace std;

int
main(int argc, char* argv[])
{

  if(argc < 4)
    Output::showError("IP Port, and file Are Required");

  char* ip = argv[1];
  char* port = argv[2];

  Client client(ip, port);
  client.requestFile(argv[3]);
}