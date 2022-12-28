#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <sstream>
#include <algorithm>
#include <fstream>


#ifndef OUTPUT
#include "../Utils/Output.h"
#endif

#include "../Utils/helperFunctions.h"

#include "Server.h"

/*
  Server applies multiprocessing approach to communicate to clients simultaneously as processes are more reliable that now if one process crashes, it won't affect the others unlike threads
*/

using namespace std;

int
main(int argc, char* argv[])
{
  if(argc < 2)
    Output::showError("No Port Specified");

  char* port = argv[1];
  char* ip = NULL;
  
  if(argc >= 3)
    ip = argv[2];

  Server server(ip, port);
  server.start();
}