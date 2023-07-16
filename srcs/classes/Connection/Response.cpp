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
        if (_offset < _message_size) // sending message (the status line and the fileds in short)
            buffer[length] = _message[_offset++];
        else break; // nothing to send
        ++length;
    }
    return (length);
}

void Response::seek_back(const size_t & amount)
{
    if (_offset < _message_size)
        _offset -= amount;
}

bool Response::is_done()
{
    return (_offset == _message_size/* && we read the hole body*/);
}

void Response::serving()
{
    _message.assign(response);
    std::cout << "RESPONSE = ["<<_message<<']' << std::endl;
    _message_size = _message.length();
}
