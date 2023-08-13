#include "includes.hpp"

WebServ::WebServ()
: _number_of_connections()
{}

Connection & WebServ::get_connection(const size_t & index)
{
    return (*_conns[index]);
}

void WebServ::add_connection(const bool & isListen, const int & fdsock, std::vector<Server*> & servers)
{
    _sockets.push_back((SOCKET_POLL){\
    .fd=fdsock,\
    .events=POLLIN|POLLERR|POLLHUP|POLLNVAL,\
    .revents=0\
    });
    _conns.push_back(new Connection(isListen, _sockets.back(), servers));
    ++_number_of_connections;
    for (size_t i = 0; i < _number_of_connections; ++i)
        _conns[i]->_socket = &_sockets[i];
}

void WebServ::remove_connection(const size_t & index)
{
    delete _conns[index];
    _conns.erase(_conns.begin() + index);
    _sockets.erase(_sockets.begin() + index);
    --_number_of_connections;
    for (size_t i = 0; i < _number_of_connections; ++i)
        _conns[i]->_socket = &_sockets[i];
}
