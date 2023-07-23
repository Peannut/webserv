#include "includes.hpp"

void Request::method_mode(const char & c)
{
    if (c == ' ')
    {
        _mode = path_m;
        if (__tmp1 == "GET") _method = GET_method;
        else if (__tmp1 == "POST") _method = POST_method;
        else if (__tmp1 == "DELETE") _method = DELETE_method;
        else set_error(501);
        __tmp1.clear();
    }
    else
    {
        if (!isMethodChar(c) || __tmp1.size() > 6) set_error(400);
        else __tmp1.push_back(c);
    }
}

void Request::path_mode(const char & c)
{
    if (c == '?')
    {
        _uri.push_back(c);
        _queries.push_back(make_pair(std::string(), std::string()));
        _mode = query_key_m;
    }
    else if (c == ' ')
    {
        _mode = version_m;
        if (_uri.length() > URI_LIMIT) set_error(414);
    }
    else if (c == '%')
    {
        _mode = encoding_m;
    }
    else
    {
        if (!isPathChar(c)) set_error(400);
        else
        {
            _path.push_back(c);
            _uri.push_back(c);
        }
    }
}

void Request::encoding_mode(const char & c)
{
    if (!isHEXDIG(c))
        set_error(400);
    __tmp1.push_back(c);
    if (__tmp1.size() == 2)
    {
        char decoded = (char)std::strtoull(__tmp1.data(), NULL, 16);
        __tmp1.clear();
        _path.push_back(decoded);
        _uri.push_back(decoded);
        _mode = path_m;
    }
}

void Request::query_key_mode(const char & c)
{
    if (c == '=')
    {
        _uri.push_back(c);
        _query.push_back(c);
        if (_queries.back().first.empty()) set_error(400);
        else _mode = query_val_m;
    }
    else
    {
        if (!isQueryChar(c)) set_error(400);
        else
        {
            _queries.back().first.push_back(c);
            _uri.push_back(c);
            _query.push_back(c);
        }
    }
}

void Request::query_val_mode(const char & c)
{
    if (c == ' ')
    {
        _mode = version_m;
        if (_uri.length() > URI_LIMIT) set_error(414);
    }
    else if (c == '&')
    {
        _uri.push_back(c);
        _query.push_back(c);
        _queries.push_back(make_pair(std::string(), std::string()));
        _mode = query_key_m;
    }
    else
    {
        if (!isQueryChar(c)) set_error(400);
        else
        {
            _queries.back().second.push_back(c);
            _uri.push_back(c);
            _query.push_back(c);
        }
    }
}

void Request::version_mode(const char & c)
{
    if (c == '\r')
    {
        _mode = field_CRLF_m;
        if (_version.size() != 6 && _version.size() != 8)
            set_error(400);
        else if (_version[0] != 'H' || _version[1] != 'T' || _version[2] != 'T' || _version[3] != 'P' || _version[4] != '/')
            set_error(400);
        else if (!std::isdigit(_version[5]) && (_version.size() == 8 && _version[6] != '.' && !std::isdigit(_version[7])))
            set_error(400);
        else
        {
            if (_version.size() == 6)
            {
                if (_version[5] <= '1') set_error(426);
                else set_error(505);
            }
            else
            {
                if (_version[5] < '1') set_error(426);
                else if (_version[5] == '1')
                {
                    if (_version[7] < '1') set_error(426);
                    else if (_version[7] > '1') set_error(505);
                }
                else if (_version[5] > '1') set_error(505);
            }
        }
    }
    else
    {
        if (_version.size() > 8)
            set_error(400);
        else _version.push_back(c);
    }
}
