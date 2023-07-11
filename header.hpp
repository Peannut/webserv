#ifndef RESPONSE_HPP
# define RESPONSE_HPP

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <fstream>

struct metaResponse {
    int statusCode;
    std::string statusMessage;
    std::string contentType;
    std::string content;
    // std::string headers;

    metaResponse() {}
    metaResponse(int code, const std::string& message, const std::string& type, const std::string& body)
        : statusCode(code), statusMessage(message), contentType(type), content(body) {}
};

#endif