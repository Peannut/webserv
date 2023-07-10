/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoukaddo <zoukaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 20:11:27 by zoukaddo          #+#    #+#             */
/*   Updated: 2023/07/10 20:11:29 by zoukaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef LOCATION_HPP
#define LOCATION_HPP

#include "prototypes.hpp"

struct Location
{
	std::string root;
	bool autoindex;
	std::vector<std::string> index;
	std::set<std::string> methods;
	std::pair<std::string, std::string> CGI;
	std::string upload_path;
	std::pair<short,std::string> redirect; // code and url

	Location();
};

#endif // LOCATION_HPP
