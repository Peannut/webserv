/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwina <zwina@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 17:44:17 by zwina             #+#    #+#             */
/*   Updated: 2023/06/23 23:07:51 by zwina            ###   ########.fr       */
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
	size_t client_max_body_size; // client boy max size
	std::map<short, std::string> error_pages; // status code and it filepath

	Server();
	std::string get_host();
	std::string get_port();
};

#endif // SERVER_HPP
