/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connection.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwina <zwina@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 17:44:20 by zwina             #+#    #+#             */
/*   Updated: 2023/07/06 14:50:21 by zwina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include "prototypes.hpp"

struct Connection
{
    bool _isListen;
    bool _isMustServeNow;
    SOCKET_POLL *_socket;
    const Server *_srv;
    const std::string * _loc_path;
    const Location * _loc_obj;
    Request *_req;
    Response *_res;

    Connection(const bool & isListen, SOCKET_POLL & socket);
    ~Connection();

    SOCKET_POLL & get_socket();
    SOCKET_FD & get_fdsock();
    const Server & get_srv(void);
    const std::string & get_loc_path(void);
    const Location & get_loc_obj(void);
    Request & get_req(void);
    Response & get_res(void);

    void set_srv(const Server & srv);
    void set_loc(const std::string & loc_path, const Location & loc_obj);

    bool can_read();
    bool can_write();
    bool is_error();
    void flip_flag(const short & flag);
    void serving();
};

#endif // CONNECTION_HPP
