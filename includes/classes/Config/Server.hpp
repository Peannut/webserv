/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoukaddo <zoukaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 20:11:24 by zoukaddo          #+#    #+#             */
/*   Updated: 2023/07/10 20:11:25 by zoukaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef SERVER_HPP
#define SERVER_HPP

#include "prototypes.hpp"

struct Server
{
	std::pair<int, short> listen;
	std::vector<std::string> server_names;
	std::map<std::string, Location> locations;
	size_t client_body_size;
	std::map<short, std::string> error_pages;

	Server();
};

#endif // SERVER_HPP
