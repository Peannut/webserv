#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include "prototypes.hpp"

struct Connection
{
    bool _isListen;
    const time_t _startTime;
    SOCKET_POLL *_socket;
    std::vector<Server*> & _srvs;
    Server * _srv;
    Location * _loc;
    Request *_req;
    Response *_res;

    Connection(const bool & isListen, SOCKET_POLL & socket, std::vector<Server*> & servers);
    ~Connection();

    time_t get_passed_time();
    SOCKET_POLL & get_socket();
    SOCKET_FD & get_fdsock();

    bool can_read();
    bool can_write();
    bool is_error();
    void flip_read_to_write();
};

#endif // CONNECTION_HPP
