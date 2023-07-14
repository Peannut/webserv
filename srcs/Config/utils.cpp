/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwina <zwina@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 09:40:39 by zoukaddo          #+#    #+#             */
/*   Updated: 2023/07/13 19:50:59 by zwina            ###   ########.fr       */
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

std::string convertToIPAddress(size_t ip)
{
    std::string str;
    std::stringstream ss;

    std::cout << "HELLO 1" << std::endl;
    for (int i = 0; i < 4; ++i)
    {
        int octet = (ip >> (8 * (3 - i))) & 255;
        ss << octet << '.';
    }
    str.assign(ss.str());
    str.erase(str.end() - 1);

    return str;
}

std::string convertPortToString(short port)
{
    std::stringstream ss;
    ss << port;
    return ss.str();
}
