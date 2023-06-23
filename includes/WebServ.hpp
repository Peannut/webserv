#ifndef WEBSERV_HPP
#define WEBSERV_HPP

#include "prototypes.hpp"

struct WebServ
{
    Config _conf;
    std::vector<Connection> _conns;
};

#endif // WEBSERV_HPP
