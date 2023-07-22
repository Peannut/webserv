#ifndef HEADER_HPP
#define HEADER_HPP

// Includes
#include <iostream>
#include <locale>
#include <utility>

#include <algorithm>
#include <iterator>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>
#include <set>

#include <cstdlib>
#include <cstring>
#include <cerrno>

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netdb.h>
#include <fcntl.h>
#include <poll.h>

#include "prototypes.hpp"

// Classes Definitions
#include "classes/Connection/Request.hpp"
#include "classes/Connection/Response.hpp"
#include "classes/Connection/Connection.hpp"
#include "classes/Config/Location.hpp"
#include "classes/Config/Server.hpp"
#include "classes/Config/Config.hpp"
#include "classes/WebServ.hpp"

#include <sys/stat.h> // remove this after

#endif // HEADER_HPP
