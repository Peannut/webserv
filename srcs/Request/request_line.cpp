#include "includes.hpp"

void Request::method_mode(const char & c)
{
    if (c == ' ')
    {
        _mode = path_m;
        if (__tmp1 == "GET") _method = get_method;
        else if (__tmp1 == "POST") _method = post_method;
        else if (__tmp1 == "DELETE") _method = delete_method;
        else _mode = error_m;
    }
    else
    {
        if (!isMethodChar(c) || __tmp1.size() > 6) setError(code_400_e);
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
    }
    else
    {
        if (!isPathChar(c)) setError(code_400_e);
        else
        {
            _path.push_back(c);
            _uri.push_back(c);
        }
    }
}

void Request::query_key_mode(const char & c)
{
    if (c == '=')
    {
        _uri.push_back(c);
        if (_queries.back().first.empty()) setError(code_400_e);
        else _mode = query_val_m;
    }
    else
    {
        if (!isQueryChar(c)) setError(code_400_e);
        else
        {
            _queries.back().first.push_back(c);
            _uri.push_back(c);
        }
    }
}

void Request::query_val_mode(const char & c)
{
    if (c == ' ')
    {
        _mode = version_m;
    }
    else if (c == '&')
    {
        _uri.push_back(c);
        _queries.push_back(make_pair(std::string(), std::string()));
        _mode = query_key_m;
    }
    else
    {
        if (!isQueryChar(c)) setError(code_400_e);
        else
        {
            _queries.back().second.push_back(c);
            _uri.push_back(c);
        }
    }
}

void Request::version_mode(const char & c)
{
    if (c == '\r')
    {
        _mode = field_CRLF_m;
    }
    else
    {
        if (_version.size() == 8)
        {
            if (_version[0] != 'H' || \
                _version[1] != 'T' || \
                _version[2] != 'T' || \
                _version[3] != 'P' || \
                _version[3] != '/')
                setError(code_400_e);
            else if (_version[4] != '1' || \
                     _version[5] != '.' || \
                     _version[6] != '1')
                setError(code_505_e);
        }
        else if (_version.size() > 8)
            setError(code_400_e);
        else _version.push_back(c);
    }
}
