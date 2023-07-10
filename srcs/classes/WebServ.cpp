/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WebServ.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwina <zwina@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 15:03:12 by zwina             #+#    #+#             */
/*   Updated: 2023/07/09 15:29:10 by zwina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.hpp"

WebServ::WebServ()
: _number_of_connections()
{}

Connection & WebServ::get_connection(const size_t & index)
{
    return (*_conns[index]);
}

SOCKET_POLL & WebServ::get_socket(const size_t & index)
{
    return (_sockets[index]);
}

void WebServ::add_connection(const bool & isListen, const int & fdsock)
{
    std::cout << ANSI_YELLOW;
    std::cout << "{[(---------------------------------------Adding";
    _sockets.push_back((SOCKET_POLL){.fd=fdsock});
    _conns.push_back(new Connection(isListen, _sockets.back()));
    ++_number_of_connections;
    for (size_t i = 0; i < _number_of_connections; ++i)
        _conns[i]->_socket = &_sockets[i];
    std::cout << "---------------------------------------)]}" << std::endl;
    std::cout << ANSI_RESET;
}

void WebServ::remove_connection(const size_t & index)
{
    std::cout << ANSI_YELLOW;
    std::cout << "{[(---------------------------------------Closing";
    delete _conns[index];
    _conns.erase(_conns.begin() + index);
    _sockets.erase(_sockets.begin() + index);
    --_number_of_connections;
    for (size_t i = 0; i < _number_of_connections; ++i)
        _conns[i]->_socket = &_sockets[i];
    std::cout << "---------------------------------------)]}" << std::endl;
    std::cout << ANSI_RESET;
}