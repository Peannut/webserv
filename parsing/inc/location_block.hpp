/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   location_block.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoukaddo <zoukaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 08:25:53 by zoukaddo          #+#    #+#             */
/*   Updated: 2023/07/04 16:20:57 by zoukaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _LOCATION_BLOCK_HPP_
# define _LOCATION_BLOCK_HPP_

#include "webserv.hpp"

struct location_block
{
	std::string root;
	bool autoindex;
	std::vector<std::string> index;
	std::set<std::string> methods;
	std::pair<std::string, std::string> CGI;
	std::string upload_path;
	std::pair<short,std::string> redirect; // code and url

	
	location_block() : autoindex(0) {}
	
};

#endif