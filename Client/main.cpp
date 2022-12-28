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
#include "../Utils/helperFunctions.h"


#include "Client.h"

using namespace std;

int
main(int argc, char* argv[])
{

  if(argc < 5)
    Output::showError("IP and Port Are Required");

  char* ip = argv[1];
  char* port = argv[2];

  Client client(ip, port);

  if(string(argv[3]) == "GET")
    client.sendRequest(string(argv[3]) + " " + string(argv[4]));
  else if(string(argv[3]) == "POST")
    client.upload(argv[4]);

}