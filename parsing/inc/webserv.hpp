/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoukaddo <zoukaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 19:44:15 by zoukaddo          #+#    #+#             */
/*   Updated: 2023/07/04 23:24:21 by zoukaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _WEBSERV_HPP_
# define _WEBSERV_HPP_



#include <iostream>
#include <string>
#include <map>
#include <utility>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iterator> 

#include "location_block.hpp"
#include "server_block.hpp"
#include "web.hpp"

int line_empty(const std::string& line);
ssize_t stringToLong(const std::string& str);
std::vector<std::string> split(const std::string& str, char lim);


#endif 