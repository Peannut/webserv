/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fields.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwina <zwina@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 11:25:51 by zwina             #+#    #+#             */
/*   Updated: 2023/07/10 10:33:42 by zwina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.hpp"

void Request::field_CRLF_mode(const char & c)
{
    if (c != '\n')
        setError(code_400_e);
    else
    {
        _mode = field_key_m;
        if (!__tmp1.empty() && !__tmp2.empty())
        {
            if (__tmp1 == "CONTENT-LENGTH")
            {
                if (!isContentLengthValValid(__tmp2)) setError(code_400_e);
                else setTransferContent();
            }
            else if (__tmp1 == "TRANSFER-ENCODING")
            {
                if (__tmp2 != "chunked") setError(code_501_e);
                else setTransferChunk();
            }
            if (_mode != error_m) _fields[__tmp1] = __tmp2;
            __tmp1.clear();
            __tmp2.clear();
        }
    }
}

void Request::setTransferContent()
{
    if (_transfer == none_tr)
    {
        _transfer = content_tr;
        _transfer_content_len = std::stoull(__tmp2);
        std::cout << "_content_length => |" << _transfer_content_len << '|' << std::endl;
    }
    else
        setError(code_400_e);
}

void Request::setTransferChunk()
{
    if (_transfer == none_tr)
    {
        _transfer = chunk_tr;
        std::cout << "_transfer_encoding => |chunked|" << std::endl;
    }
    else
        setError(code_501_e);
}

void Request::field_key_mode(const char & c)
{
    if (c == '\r' && __tmp1.empty() && __tmp2.empty())
    {
        _mode = field_last_CRLF_m;
    }
    else if (c == ':')
    {
        if (__tmp1.empty()) setError(code_400_e);
        else _mode = field_val_m;
    }
    else
    {
        if (!isTchar(c)) setError(code_400_e);
        else __tmp1.push_back(c);
    }
}

void Request::field_val_mode(const char & c)
{
    if (c == '\r')
    {
        toupperFieldKey(__tmp1);
        trimFieldVal(__tmp2);
        if (__tmp2.empty()) setError(code_400_e);
        else _mode = field_CRLF_m;
    }
    else
    {
        if (!isVchar(c)) setError(code_400_e);
        else __tmp2.push_back(c);
    }
}

void Request::field_last_CRLF_mode(const char & c)
{
    if (c != '\n')
        setError(code_400_e);
    else
    {
        if (_fields.find("HOST") == _fields.end())
            setError(code_400_e);
        if (_transfer == none_tr)
            setError(code_411_e); // HNA FIN SAALIIITT
        else
        {
            if (_transfer == content_tr && _transfer_content_len == 0) _mode = success_m;
            else if (_transfer == content_tr) _mode = body_content_m;
            else if (_transfer == chunk_tr) _mode = body_length_m;
        }
    }
}
