/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connection.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwina <zwina@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 15:03:26 by zwina             #+#    #+#             */
/*   Updated: 2023/06/24 15:03:27 by zwina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.hpp"

Connection::Connection(const bool & isListen, const int & fdsock)
: _isListen(isListen)
, _req((isListen) ? NULL : (new Request()))
, _res((isListen) ? NULL : (new Response()))
{
    _socket.fd = fdsock;
    _socket.events = POLLSTANDARD;
    _socket.revents = (short)0;
}

Connection::~Connection()
{
    close(_socket.fd);
}

Request & Connection::get_req(void)
{
    return *_req;
}
Response & Connection::get_res(void)
{
    return *_res;
}
