/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_block.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoukaddo <zoukaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 08:22:42 by zoukaddo          #+#    #+#             */
/*   Updated: 2023/06/20 11:09:17 by zoukaddo         ###   ########.fr       */
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

};

#endif // !_SERVER_BLOCK_HPP_
