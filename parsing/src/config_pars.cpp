/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_pars.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoukaddo <zoukaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 08:42:48 by zoukaddo          #+#    #+#             */
/*   Updated: 2023/06/17 08:57:45 by zoukaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../webserv.hpp"

int line_empty(const std::string& line)
{
	for (size_t i = 0; i < line.size(); i++)
	{
		if (!std::isspace(line[i]))
			return (0);
	}
	return (1);
}

void Webserver::setupServer(std::ifstream& file)
{
	server_block server;
	for (std::string line; std::getline(file, line);)
	{
		if (line_empty(line))
			continue ;
		if (!line.compare(0,7,"server:"))
			break ;
		else
			throw std::runtime_error("Error: invalid server directive");
	}
	
}

void	setupconfig(const std::string& filename)
{
	std::ifstream file(filename);

	if (!file.is_open())
		throw std::runtime_error("Error: cannot open config file");
	for (std::string line; std::getline(file, line);)
	{
		if (line_empty(line))
			continue ;
		std::cout << line << std::endl;
		if (!line.compare(0,7,"server:"))
			;
		else
			throw std::runtime_error("Error: invalid directive");
		
	}
}