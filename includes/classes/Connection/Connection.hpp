/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connection.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwina <zwina@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 17:44:20 by zwina             #+#    #+#             */
/*   Updated: 2023/06/24 01:34:18 by zwina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include "prototypes.hpp"

struct Connection
{
    bool _isListen;
    SOCKET _socket;
    Request *_req;
    Response *_res;

    Connection(const bool & isListen, const int & fdsock);
    ~Connection();
    Request & get_req(void);
    Response & get_res(void);
};

#endif // CONNECTION_HPP
