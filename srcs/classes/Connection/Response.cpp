#include "includes.hpp"

Response::Response(const Request *req)
: request(req)
, _message_size()
, _offset()
{}

size_t Response::extract()
{
    size_t length = 0;
    while (length < BUFFER_SIZE)
    {
        if (_offset < _message_size)
            buffer[length] = _message[_offset];
        else if (bodyFile.is_open() && !bodyFile.eof()) {
            bodyFile >> buffer[length];
        }
        else break;
        ++length;
        ++_offset;
    }
    return (length);
}

void Response::seek_back(const size_t & amount)
{
    if (bodyFile.is_open()) {
        size_t pos = bodyFile.tellg();
        bodyFile.seekg((pos <= amount)? 0 : pos - amount);
    }
    _offset -= amount;
}

bool Response::is_done()
{
    return (_offset >= _message_size && (!bodyFile.is_open() || bodyFile.eof()));
}

void Response::serving(const Server &server, const Location *loc, const std::string &loc_Path)
{
    UNUSED(server);
    UNUSED(loc);
    UNUSED(loc_Path);
    _message.assign(response);
    _message_size = _message.length();
    std::cout << "RESPONSE = ["<<_message<<']' << std::endl;
}
