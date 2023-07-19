#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include "prototypes.hpp"

struct Response
{
    const Request *request;
    int statusCode;
    std::string statusMessage;
    std::string contentType;
    std::string content;
    std::string Headers;
    std::fstream bodyFile;
    std::string _message;
    size_t _message_size;
    size_t _offset;

    Response(const Request *req);

    size_t extract();
    void seek_back(const size_t & amount);
    bool is_done();
    void serving(const Server &server, const Location *loc, const std::string &loc_Path);
};

#endif // RESPONSE_HPP
