#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include "prototypes.hpp"

struct Connection
{
    struct pollfd _socket;
    Request *_req;
    Response *_res;
};

#endif // CONNECTION_HPP
