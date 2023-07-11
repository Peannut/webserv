/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   body.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwina <zwina@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 11:26:06 by zwina             #+#    #+#             */
/*   Updated: 2023/07/10 10:21:02 by zwina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.hpp"

void Request::body_content_mode(const char & c)
{
    if (_transfer_content_len == 0)
        setError(code_400_e);
    else
    {
        _body.push_back(c);
        --_transfer_content_len;
        if (_transfer_content_len == 0)
            _mode = success_m;
    }
}

void Request::body_length_mode(const char & c)
{
    if (c == '\r')
        _mode = body_length_CRLF_m;
    else
    {
        if (!std::isalnum(c)) setError(code_400_e);
        else __tmp1.push_back(c);
    }
}

void Request::body_length_CRLF_mode(const char & c)
{
    if (c != '\n')
        setError(code_400_e);
    else
    {
        _transfer_content_len = std::stoull(__tmp1, 0, 16);
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
        _body.push_back(c);
        --_transfer_chunk_len;
    }
}

void Request::body_chunk_CRLF_mode(const char & c)
{
    if (c != '\n')
        setError(code_400_e);
    else
    {
        if (_transfer_content_len == 0) _mode = success_m;
        else _mode = body_length_m;
    }
}
