/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connection.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwina <zwina@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 17:44:20 by zwina             #+#    #+#             */
/*   Updated: 2023/08/09 15:04:48 by zwina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include "prototypes.hpp"

struct Connection
{
    bool _isListen;
    const time_t _startTime;
    SOCKET_POLL *_socket;
    std::vector<Server*> & _srvs;
    Server * _srv;
    Location * _loc;
    Request *_req;
    Response *_res;

    Connection(const bool & isListen, SOCKET_POLL & socket, std::vector<Server*> & servers);
    ~Connection();

    time_t get_passed_time();
    SOCKET_POLL & get_socket();
    SOCKET_FD & get_fdsock();
    Request & get_req(void);
    Response & get_res(void);

    void set_srv(const Server & srv);
    void set_srv(std::vector<Server *> & _srvs);
    void set_loc(const std::string & loc_path, const Location & loc_obj);

    bool can_read();
    bool can_write();
    bool is_error();
    void flip_flag(const short & flag);

    void serving();
};

#endif // CONNECTION_HPP
