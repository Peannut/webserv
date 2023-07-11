#include "includes.hpp"

Connection::Connection(const bool & isListen, SOCKET_POLL & socket)
: _isListen(isListen)
, _isMustServeNow(false)
, _socket(&socket)
, _req((isListen) ? NULL : (new Request()))
, _res((isListen) ? NULL : (new Response()))
{}

Connection::~Connection()
{
    close(_socket->fd);
}

Request & Connection::get_req(void)
{
    return *_req;
}
Response & Connection::get_res(void)
{
    return *_res;
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
void Connection::flip_flag(const short & flag)
{
    _socket->events = _socket->events ^ flag;
}

void Connection::serving()
{
    _req->serving();
    _res->serving();
}
