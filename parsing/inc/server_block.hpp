/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_block.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoukaddo <zoukaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 08:22:42 by zoukaddo          #+#    #+#             */
/*   Updated: 2023/07/04 23:18:30 by zoukaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _SERVER_BLOCK_HPP_
# define _SERVER_BLOCK_HPP_
#include "webserv.hpp"

struct server_block
{
	std::pair<int, short> listen;
	std::vector<std::string> server_names;
	std::map<std::string, location_block> locations;
	size_t client_body_size;
	std::map<short, std::string> error_pages;

	server_block(): client_body_size(0)
	{
	}

};

#endif // !_SERVER_BLOCK_HPP_
