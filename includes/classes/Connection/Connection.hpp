#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include "prototypes.hpp"

struct Connection
{
    bool _isListen;
    bool _isMustServeNow;
    SOCKET_POLL *_socket;
    Request *_req;
    Response *_res;

    Connection(const bool & isListen, SOCKET_POLL & socket);
    ~Connection();
    Request & get_req(void);
    Response & get_res(void);
    bool can_read();
    bool can_write();
    bool is_error();
    void flip_flag(const short & flag);
    void serving();
};

#endif // CONNECTION_HPP
