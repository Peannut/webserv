/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoukaddo <zoukaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 09:40:39 by zoukaddo          #+#    #+#             */
/*   Updated: 2023/07/10 20:12:28 by zoukaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.hpp"

int line_empty(const std::string& line)
{
	for (size_t i = 0; i < line.size(); i++)
	{
		if (!std::isspace(line[i]))
			return (0);
	}
	return (1);
}

std::vector<std::string> split(const std::string& str, char lim)
{
    std::vector<std::string> tokens;
    size_t start = 0, end = 0;
    while ((end = str.find(lim, start)) != std::string::npos) {
        if (!line_empty(str.substr(start, end - start)))
            tokens.push_back(str.substr(start, end - start));
        start = end + 1;
    }
    if (!line_empty(str.substr(start)))
        tokens.push_back(str.substr(start));
    return tokens;
}


long int ft_stringtolong(const std::string& str)
{
    long int result;
    std::istringstream iss(str);

    if (!(iss >> result) || !iss.eof()) {
        throw std::invalid_argument("ft_stringtoolong: invalid argument");
    }
    return result;
}