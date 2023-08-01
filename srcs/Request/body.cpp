#include "includes.hpp"

size_t Request::body_content_mode(const std::string & buffer, const size_t & i)
{
    const size_t length = buffer.size() - i;
    if (length <= _transfer_content_len)
    {
        try {
            _body.append(buffer.data() + i);
            _transfer_content_len -= length;
            if (_transfer_content_len == 0)
                _mode = success_m;
        } catch (const std::exception &e) {
            set_error(413);
        }
    }
    else
        set_error(400);
    return buffer.size() - 1;
}

void Request::body_length_mode(const char & c)
{
    if (c == '\r')
        _mode = body_length_CRLF_m;
    else
    {
        if (!std::isalnum(c)) set_error(400);
        else __tmp1.push_back(c);
    }
}

void Request::body_length_CRLF_mode(const char & c)
{
    if (c != '\n')
        set_error(400);
    else
    {
        _transfer_content_len = std::strtoull(__tmp1.data(), NULL, 16);
        _transfer_chunk_len = _transfer_content_len;
        __tmp1.clear();
        _mode = body_chunk_m;
    }
}

void Request::body_chunk_mode(const char & c)
{
    if (_transfer_chunk_len == 0)
    {
        if (c != '\r') _mode = body_chunk_CRLF_m;
        else _mode = body_chunk_CRLF_m;
    }
    else
    {
        if (_body.size() == _transfer_content_max_len)
            set_error(413);
        else
        {
            try {
                _body.push_back(c);
                --_transfer_chunk_len;
            } catch (const std::exception & e) {
                set_error(413);
            }
        }
    }
}

void Request::body_chunk_CRLF_mode(const char & c)
{
    if (c != '\n')
        set_error(400);
    else
    {
        if (_transfer_content_len == 0) _mode = success_m;
        else _mode = body_length_m;
    }
}
