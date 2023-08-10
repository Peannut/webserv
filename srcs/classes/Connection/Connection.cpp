#include "includes.hpp"

Connection::Connection(const bool & isListen, SOCKET_POLL & socket, std::vector<Server*> & servers)
: _isListen(isListen)
, _startTime(time(NULL))
, _socket(&socket)
, _srvs(servers)
, _srv(servers[0])
, _loc(NULL)
, _req((isListen) ? NULL : (new Request(*this)))
, _res((isListen) ? NULL : (new Response(_req)))
{}

Connection::~Connection()
{
    close(_socket->fd);
    if (_req) delete _req;
    if (_res) delete _res;
}

time_t Connection::get_passed_time()
{
    return (time(NULL) - _startTime);
}

SOCKET_POLL & Connection::get_socket()
{
    return *_socket;
}
SOCKET_FD & Connection::get_fdsock()
{
    return _socket->fd;
}
bool Connection::can_read()
{
    return (_socket->revents & (POLLIN));
}
bool Connection::can_write()
{
    return (_socket->revents & (POLLOUT));
}
bool Connection::is_error()
{
    return (_socket->revents & (POLLERR|POLLHUP|POLLNVAL));
}
void Connection::flip_read_to_write()
{
    _socket->events = _socket->events ^ POLLIN;
    _socket->events = _socket->events ^ POLLOUT;
}
