/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoukaddo <zoukaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 09:40:39 by zoukaddo          #+#    #+#             */
/*   Updated: 2023/06/20 10:56:47 by zoukaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/webserv.hpp"

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


ssize_t stringToLong(const std::string& str)
{
    std::istringstream iss(str);
    long int result;
    char remainder;
    if (!(iss >> result) || (iss >> remainder)) {
        throw (std::invalid_argument("stringTolong: invalid argument"));
    }
    return result;
}