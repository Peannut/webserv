#ifndef WEBSERV_HPP
#define WEBSERV_HPP

#include "prototypes.hpp"

struct WebServ
{
    Config _conf;
    size_t _number_of_connections;
    std::vector<Connection*> _conns;
    std::vector<SOCKET_POLL> _sockets;

    WebServ();

    Connection & get_connection(const size_t & index);
    void add_connection(const bool & isListen, const int & fdsock, std::vector<Server *> & servers);
    void remove_connection(const size_t & index);
};

#endif // WEBSERV_HPP
