/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoukaddo <zoukaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 08:22:42 by zoukaddo          #+#    #+#             */
/*   Updated: 2023/08/01 15:10:17 by zoukaddo         ###   ########.fr       */
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
