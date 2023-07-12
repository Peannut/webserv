/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoukaddo <zoukaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 20:11:24 by zoukaddo          #+#    #+#             */
/*   Updated: 2023/07/12 07:58:18 by zoukaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef SERVER_HPP
#define SERVER_HPP

#include "prototypes.hpp"

struct Server
{
	std::pair<int, short> listen; // port on 32bit format and the port
	std::vector<std::string> server_names; // vector of server names
	std::map<std::string, Location> locations; // path location | location
	size_t client_body_size; // client boy max size
	std::map<short, std::string> error_pages; // status code and it filepath

	Server();
	std::string get_host();
	std::string get_port();
};

#endif // SERVER_HPP