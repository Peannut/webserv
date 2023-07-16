#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include "prototypes.hpp"

struct Response
{
    const Request *request;
    std::string _message;
    size_t _message_size;
    size_t _offset;

    Response(const Request *req);

    size_t extract();
    void seek_back(const size_t & amount);
    bool is_done();
    void serving();
};

#endif // RESPONSE_HPP
