/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WebServ.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwina <zwina@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 17:44:32 by zwina             #+#    #+#             */
/*   Updated: 2023/06/24 03:40:33 by zwina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_HPP
#define WEBSERV_HPP

#include "prototypes.hpp"

struct WebServ
{
    Config _conf;
    size_t _number_of_servers;
    std::vector<Connection*> _conns;
    std::vector<SOCKET> _sockets;

    WebServ();

    Connection & get_connection(const size_t & index);
    SOCKET & get_socket(const size_t & index);
    void add_connection(const bool & isListen, const int & fdsock);
    void remove_connection(const size_t & index);
    bool is_listen_connection(const size_t & index);
};

#endif // WEBSERV_HPP
