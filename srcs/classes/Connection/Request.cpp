/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwina <zwina@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 15:03:22 by zwina             #+#    #+#             */
/*   Updated: 2023/07/10 11:09:33 by zwina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.hpp"

Request::Request()
: _mode(method_m)
, _error(none_e)
, _transfer(none_tr)
, _method(none_method)
, _transfer_content_len()
, _transfer_chunk_len()
{}

bool Request::concatenate(const std::string & buffer)
{
    for (size_t sz = buffer.size(), i = 0; i < sz; ++i) {
        const char & c = buffer[i];
        if (_mode == success_m) _mode = error_m;
        switch (_mode)
        {
            // request_line
            case method_m:          method_mode(c); break;
            case path_m:            path_mode(c); break;
            case query_key_m:       query_key_mode(c); break;
            case query_val_m:       query_val_mode(c); break;
            case version_m:         version_mode(c); break;
            // fields
            case field_CRLF_m:      field_CRLF_mode(c); break;
            case field_key_m:       field_key_mode(c); break;
            case field_val_m:       field_val_mode(c); break;
            case field_last_CRLF_m: field_last_CRLF_mode(c); break;
            // body
            case body_content_m:    body_content_mode(c); break;
            case body_length_m:     body_length_mode(c); break;
            case body_length_CRLF_m:body_length_CRLF_mode(c); break;
            case body_chunk_m:      body_chunk_mode(c); break;
            case body_chunk_CRLF_m: body_chunk_CRLF_mode(c); break;

            case error_m:           break;
            case success_m:         break;
        }
        if (_mode == error_m) break;
        _message.push_back(c);
    }
    if (_mode == success_m)
    {
        std::cout << ANSI_BOLD;
        std::cout << "==>success_m<==" << std::endl;
        std::cout << ANSI_RESET;
        return true;
    }
    else if (_mode == error_m)
    {
        std::cout << ANSI_BOLD;
        std::cout << "==>error_m<==" << std::endl;
        std::cout << ANSI_RESET;
        return true;
    }
    return false;
}

void Request::serving(void)
{
    std::cout << "REQUEST = [" << std::endl;
    std::cout << "message => |" << _message << '|' << std::endl;
    std::cout << "method =>\t\t|";
    if (_method == get_method) std::cout << "GET";
    if (_method == post_method) std::cout << "POST";
    if (_method == delete_method) std::cout << "DELETE";
    std::cout << '|' << std::endl;
    std::cout << "uri =>\t\t\t|" << _uri << '|' << std::endl;
    std::cout << "path =>\t\t\t|" << _path << '|' << std::endl;
    std::cout << "number_of_queries => |" << _queries.size() << '|' << std::endl;
    for (size_t sz = _queries.size(), i = 0; i < sz; ++i)
        std::cout << "query =>\t\t|" << _queries[i].first << "->" << _queries[i].second << '|' << std::endl;
    std::cout << "version =>\t\t|" << _version << '|' << std::endl;
    std::cout << "number_of_fields => |" << _fields.size() << '|' << std::endl;
    for (std::map<std::string, std::string>::iterator it = _fields.begin(); it != _fields.end(); ++it)
        std::cout << "field =>\t\t|" << it->first << "|:|" << it->second << '|' << std::endl;
    std::cout << "body =>\t\t\t|" << _body << '|' << std::endl;
    std::cout << ']' << std::endl;
}

void Request::setError(const Errors & e)
{
    _mode = error_m;
    _error = e;
}
