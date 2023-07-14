/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwina <zwina@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 08:22:42 by zoukaddo          #+#    #+#             */
/*   Updated: 2023/07/13 18:01:30 by zwina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "includes.hpp"

Server::Server(): client_max_body_size(0)
{}

std::string Server::get_host()
{
	return convertToIPAddress(listen.first);
}

std::string Server::get_port()
{
	return convertPortToString(listen.second);
}
