/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoukaddo <zoukaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 20:11:27 by zoukaddo          #+#    #+#             */
/*   Updated: 2023/07/12 07:31:22 by zoukaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef LOCATION_HPP
#define LOCATION_HPP

#include "prototypes.hpp"

struct Location
{
	std::string root; // root path
	bool autoindex; // on or off 
	std::vector<std::string> index; // index
	std::set<std::string> methods; // set of methods for get and post and delete only
	std::pair<short,std::string> redirect; // code and url
	std::string upload_pass; // upload pass path
	std::pair<std::string, std::string> cgi_bin; // extension and path

	Location();
};

