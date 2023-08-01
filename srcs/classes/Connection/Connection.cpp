#include "includes.hpp"

Connection::Connection(const bool & isListen, SOCKET_POLL & socket)
: _isListen(isListen)
, _startTime(time(NULL))
, _socket(&socket)
, _srv(NULL)
, _loc_path(NULL)
, _loc_obj(NULL)
, _req((isListen) ? NULL : (new Request()))
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
const Server & Connection::get_srv(void)
{
    return *_srv;
}
const std::string & Connection::get_loc_path(void)
{
    return *_loc_path;
}
const Location & Connection::get_loc_obj(void)
{
    return *_loc_obj;
}
Request & Connection::get_req(void)
{
    return *_req;
}
Response & Connection::get_res(void)
{
    return *_res;
}

void Connection::set_srv(const Server & srv)
{
    _srv = &srv;
    if (_req) _req->set_max_len(srv.client_max_body_size);
}
void Connection::set_loc(const std::string & loc_path, const Location & loc_obj)
{
    _loc_path = &loc_path;
    _loc_obj = &loc_obj;
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
    _req->serving(*this);
    _res->serving(*this->_srv, this->_loc_obj, *this->_loc_path);
}
