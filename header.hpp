#ifndef HEADER_HPP
# define HEADER_HPP

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <iostream>

struct metaRequest {
    std::string _method;
    std::string _path;
    std::string _version;
    std::string _body;
    std::string _req_raw;
    std::vector<std::pair<std::string, std::string>> _headers;
};

struct metaResponse {
    int statusCode;
    std::string statusMessage;
    std::string contentType;
    std::string content;

    metaResponse(int code, const std::string& message, const std::string& type, const std::string& body)
        : statusCode(code), statusMessage(message), contentType(type), content(body) {}
};

#endif