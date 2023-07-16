#include "includes.hpp"

void Request::field_CRLF_mode(const char & c)
{
    if (c != '\n')
        set_error(400);
    else
    {
        _mode = field_key_m;
        if (!__tmp1.empty() && !__tmp2.empty())
        {
            toupperFieldKey(__tmp1);
            trimFieldVal(__tmp2);
            if (_method == POST_method)
            {
                if (__tmp1 == "CONTENT-LENGTH")
                {
                    _transfer_content_len = std::strtoull(__tmp2.data(), 0, 10);
                    if (!isContentLengthValValid(__tmp2)) set_error(400);
                    else set_transfer(content_tr);
                }
                else if (__tmp1 == "TRANSFER-ENCODING")
                {
                    if (__tmp2 != "chunked") set_error(501);
                    else set_transfer(chunk_tr);
                }
            }
            if (_mode != error_m) _fields[__tmp1] = __tmp2;
            __tmp1.clear();
            __tmp2.clear();
        }
    }
}

void Request::field_key_mode(const char & c)
{
    if (c == '\r' && __tmp1.empty() && __tmp2.empty())
    {
        _mode = field_last_CRLF_m;
    }
    else if (c == ':')
    {
        if (__tmp1.empty()) set_error(400);
        else _mode = field_val_m;
    }
    else
    {
        if (!isTchar(c)) set_error(400);
        else __tmp1.push_back(c);
    }
}

void Request::field_val_mode(const char & c)
{
    if (c == '\r')
    {
        if (__tmp2.empty()) set_error(400);
        else _mode = field_CRLF_m;
    }
    else
    {
        if (!isVchar(c)) set_error(400);
        else __tmp2.push_back(c);
    }
}

void Request::field_last_CRLF_mode(const char & c)
{
    if (c != '\n')
        set_error(400);
    else
    {
        if (_fields.find("HOST") == _fields.end())
            set_error(400);
        if (_method == POST_method && _transfer == none_tr)
            set_error(411);
        if (_method == POST_method && _fields.find("CONTENT-TYPE") == _fields.end())
            set_error(415);
        else
        {
            if (_method != POST_method) _mode = success_m;
            else if (_transfer == content_tr && _transfer_content_len == 0) _mode = success_m;
            else if (_transfer == content_tr)
            {
                _mode = body_content_m;
                if (_transfer_content_max_len < _transfer_content_len)
                    set_error(413);
                try {
                    _body.reserve(_transfer_content_len);
                } catch (const std::exception & e) {
                    set_error(413);
                }
            }
            else if (_transfer == chunk_tr) _mode = body_length_m;
        }
    }
}
