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

#include "Connection/Request.hpp"
#include "Connection/Response.hpp"
#include "Connection/Connection.hpp"
#include "Config/Location.hpp"
#include "Config/Server.hpp"
#include "Config/Config.hpp"
#include "WebServ.hpp"

#endif // HEADER_HPP
