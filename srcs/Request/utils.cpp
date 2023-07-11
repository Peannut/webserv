/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   characters.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwina <zwina@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 17:08:08 by zwina             #+#    #+#             */
/*   Updated: 2023/07/10 10:36:33 by zwina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.hpp"

bool isUnreserved(const char & c)
{
    return ( \
        std::isalnum(c) || \
        c == '-' || \
        c == '.' || \
        c == '_' || \
        c == '~' \
    );
}
bool isReserved(const char & c)
{
    return ( \
        c == '?' || \
        c == '=' || \
        c == '&' || \
        c == ':' \
    );
}
bool isOWS(const char & c)
{
    return ( c == ' ' || c == 9 );
}
// visible character
bool isVchar(const char & c)
{
    return ( c >= 32 && c <= 126 );
}
// any visible character except delimiter
bool isTchar(const char & c)
{
    return ( \
        isUnreserved(c) || \
        c == '!' || \
        c == '#' || \
        c == '$' || \
        c == '%' || \
        c == '&' || \
        c == '\'' || \
        c == '*' || \
        c == '+' || \
        c == '^' || \
        c == '`' || \
        c == '|' \
    );
}

bool isMethodChar(const char & c)
{
    return (
        c == 'G' || c == 'E' || c == 'T' || \
        c == 'P' || c == 'O' || c == 'S' || \
        c == 'D' || c == 'L' \
    );
}
bool isPathChar(const char & c)
{
    return (c == '/' || isUnreserved(c));
}
bool isQueryChar(const char & c)
{
    return (isUnreserved(c));
}

void toupperFieldKey(std::string & field_key)
{
    for (size_t len = field_key.size(), i = 0; i < len; ++i)
        field_key[i] = std::toupper(field_key[i]);
}
void trimFieldVal(std::string & field_val)
{
    std::string::iterator it = field_val.begin();
    while (isOWS(field_val.back()))
        field_val.pop_back();
    while (isOWS(*it))
        ++it;
    field_val.erase(field_val.begin(), it);
}

bool isContentLengthValValid(const std::string & val)
{
    for (size_t sz = val.size(), i = 0; i < sz; ++i)
        if (!std::isdigit(val[i]))
            return false;
    return true;
}
bool isTransferEncodingValValid(const std::string & val)
{
    for (size_t sz = val.size(), i = 0; i < sz; ++i)
        if (!std::islower(val[i]))
            return false;
    return true;
}
