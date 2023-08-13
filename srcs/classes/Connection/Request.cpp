#include "includes.hpp"

Request::Request(Connection & conn)
: _error()
, _method(none_method)
, _mode(method_m)
, _transfer(none_tr)
, _transfer_content_max_len(conn._srv->client_max_body_size)
, _transfer_content_len()
, _transfer_chunk_len()
, _conn(conn)
{}

bool Request::concatenate(const std::string & buffer)
{
    for (size_t sz = buffer.size(), i = 0; i < sz; ++i) {
        const char & c = buffer[i];
        if (_mode == success_m) set_error(400);
        switch (_mode)
        {
            // request_line
            case method_m:          method_mode(c); break;
            case path_m:            path_mode(c); break;
            case encoding_m:        encoding_mode(c); break;
            case query_key_m:       query_key_mode(c); break;
            case query_val_m:       query_val_mode(c); break;
            case version_m:         version_mode(c); break;
            // fields
            case field_CRLF_m:      field_CRLF_mode(c); break;
            case field_key_m:       field_key_mode(c); break;
            case field_val_m:       field_val_mode(c); break;
            case field_last_CRLF_m: field_last_CRLF_mode(c); break;
            // body
            case body_content_m:    i = body_content_mode(buffer, i); break;
            case body_length_m:     body_length_mode(c); break;
            case body_length_CRLF_m:body_length_CRLF_mode(c); break;
            case body_chunk_m:      body_chunk_mode(c); break;
            case body_chunk_CRLF_m: body_chunk_CRLF_mode(c); break;

            case error_m:           break;
            case success_m:         break;
        }
        if (_mode == error_m) break;
    }
    if (_mode == success_m)
        return true;
    else if (_mode == error_m)
        return true;
    return false;
}

void Request::matchingServer(const std::string & host)
{
    const std::vector<Server*> & _srvs = _conn._srvs;
    for (size_t i = 0; i < _srvs.size(); ++i)
    {
        const std::vector<std::string> _server_names = _srvs[i]->server_names;
        for (size_t j = 0; j < _server_names.size(); ++j)
        {
            if (host == _server_names[j])
            {
                _conn._srv = _srvs[i];
                _transfer_content_max_len = _conn._srv->client_max_body_size;
                return ;
            }
        }
    }
}

void Request::matchingLocation()
{
    typedef std::map<std::string, Location> map_locations_t;

    map_locations_t & locations = _conn._srv->locations;

    size_t maxLenMatched = 0;

    for (map_locations_t::iterator it = locations.begin(); it != locations.end(); ++it)
    {
        size_t lenMatched = matching_location(this->_path, it->first);
        if (lenMatched != 0 && maxLenMatched < lenMatched)
        {
            _conn._loc = &it->second;
            maxLenMatched = lenMatched;
        }
    }
    if (maxLenMatched == 0) { set_error(404); return; }
    else _path.insert(_path.begin(), _conn._loc->root.begin(), _conn._loc->root.end());

    std::string method = _method != GET_method ? (_method != POST_method ? "DELETE" : "POST") : "GET";
    if (_conn._loc->methods.find(method) == _conn._loc->methods.end()) set_error(405);
}

void Request::set_transfer(const Transfers & tr)
{
    if (_transfer == tr)
        set_error(400);
    else
        _transfer = tr;
}

void Request::set_error(const short & e)
{
    _mode = error_m;
    _error = e;
}

void Request::set_max_len(const size_t & n)
{
    _transfer_content_max_len = n;
}

const Methods & Request::get_method()
{
    return _method;
}
const std::string & Request::get_uri()
{
    return _uri;
}
const std::string & Request::get_path()
{
    return _path;
}
const std::string & Request::get_queries()
{
    return _query;
}
const std::pair<std::string, std::string> & Request::get_query(const size_t & index)
{
    return _queries[index];
}
const std::string & Request::get_version()
{
    return _version;
}
const std::pair<std::string, std::string> Request::get_fields(const std::string & str)
{
    return *_fields.find(str);
}
const std::string & Request::get_body()
{
    return _body;
}
