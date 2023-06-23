#ifndef HEADER_HPP
#define HEADER_HPP

#include <iostream>
#include <iomanip>
#include <unistd.h>

#include <string>
#include <vector>
#include <list>

#include <cstring>
#include <cerrno>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netdb.h>
#include <fcntl.h>
#include <poll.h>

#include "prototypes.hpp"

#include "classes/Connection/Request.hpp"
#include "classes/Connection/Response.hpp"
#include "classes/Connection/Connection.hpp"
#include "classes/Config/Location.hpp"
#include "classes/Config/Server.hpp"
#include "classes/Config/Config.hpp"
#include "classes/WebServ.hpp"

#endif // HEADER_HPP
