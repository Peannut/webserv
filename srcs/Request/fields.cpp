#include "includes.hpp"

void Request::field_CRLF_mode(const char & c)
{
    if (c != '\n')
        set_error(code_400_e);
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
                    if (!isContentLengthValValid(__tmp2)) set_error(code_400_e);
                    else set_transfer(content_tr);
                }
                else if (__tmp1 == "TRANSFER-ENCODING")
                {
                    if (__tmp2 != "chunked") set_error(code_501_e);
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
        if (__tmp1.empty()) set_error(code_400_e);
        else _mode = field_val_m;
    }
    else
    {
        if (!isTchar(c)) set_error(code_400_e);
        else __tmp1.push_back(c);
    }
}

void Request::field_val_mode(const char & c)
{
    if (c == '\r')
    {
        if (__tmp2.empty()) set_error(code_400_e);
        else _mode = field_CRLF_m;
    }
    else
    {
        if (!isVchar(c)) set_error(code_400_e);
        else __tmp2.push_back(c);
    }
}

void Request::field_last_CRLF_mode(const char & c)
{
    if (c != '\n')
        set_error(code_400_e);
    else
    {
        if (_fields.find("HOST") == _fields.end())
            set_error(code_400_e);
        if (_method == POST_method && _transfer == none_tr)
            set_error(code_411_e);
        if (_method == POST_method && _fields.find("CONTENT-TYPE") == _fields.end())
            set_error(code_415_e);
        else
        {
            if (_method != POST_method) _mode = success_m;
            else if (_transfer == content_tr && _transfer_content_len == 0) _mode = success_m;
            else if (_transfer == content_tr)
            {
                _mode = body_content_m;
                if (_transfer_content_max_len < _transfer_content_len)
                    set_error(code_413_e);
                try {
                    _body.reserve(_transfer_content_len);
                } catch (const std::exception & e) {
                    set_error(code_413_e);
                }
            }
            else if (_transfer == chunk_tr) _mode = body_length_m;
        }
    }
}
