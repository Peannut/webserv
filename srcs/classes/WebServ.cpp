/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WebServ.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwina <zwina@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 15:03:12 by zwina             #+#    #+#             */
/*   Updated: 2023/06/24 15:03:14 by zwina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.hpp"

WebServ::WebServ()
: _number_of_servers()
{}

Connection & WebServ::get_connection(const size_t & index)
{
    return (*_conns[index]);
}

SOCKET & WebServ::get_socket(const size_t & index)
{
    return (_sockets[index]);
}

void WebServ::add_connection(const bool & isListen, const int & fdsock)
{
    _conns.push_back(new Connection(isListen, fdsock));
    _sockets.push_back(_conns.back()->_socket);
    if (isListen) ++_number_of_servers;
}

void WebServ::remove_connection(const size_t & index)
{
    _sockets.erase(_sockets.begin() + index);
    _conns.erase(_conns.begin() + index);
    if (index < _number_of_servers) --_number_of_servers;
}

bool WebServ::is_listen_connection(const size_t & index)
{
    return (index < _number_of_servers);
}
