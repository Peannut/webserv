#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include "prototypes.hpp"

struct Connection
{
    const bool _isListen;
    struct pollfd _socket;
    Request *_req;
    Response *_res;

    Connection(const bool & isListen, const int & fdsock);
    ~Connection();
};

#endif // CONNECTION_HPP
