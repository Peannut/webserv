/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_pars.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoukaddo <zoukaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 08:42:48 by zoukaddo          #+#    #+#             */
/*   Updated: 2023/06/20 11:05:59 by zoukaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/webserv.hpp"

int line_empty(const std::string& line)
{
	for (size_t i = 0; i < line.size(); i++)
	{
		if (!std::isspace(line[i]))
			return (0);
	}
	return (1);
}

void Web::setup_host(std::string& host, server_block& server)
{
	size_t ip = 0;

	std::vector<std::string> ip_split = split(host, ':');
	if (ip_split.size() != 4)
		throw std::runtime_error("Error: invalid listen");
	for(int i = 0; i < 4; i++)
	{
		int ss = 0;
	}
}

void Web::setup_listen(std::string& line, server_block& server)
{
	std::string val = line.substr(8, line.size() - 8);
	if (line_empty(val))
		throw std::runtime_error("Error: listen does not have a value");
	std::vector<std::string> port = split(val, ':');
	if (port.size() != 2)
		throw std::runtime_error("Error: invalid listen");
	
}

void Web::setupServer(std::ifstream& file)
{
	server_block server;
	for (std::string line; std::getline(file, line);)
	{
		if (line_empty(line))
			continue ;
		if (!line.compare(0,8,"\tlisten"))
			;
		else
			throw std::runtime_error("Error: invalid server directive");
	}
	
}

void	Web::setupconfig(const std::string& filename)
{
	std::ifstream file(filename);

	if (!file.is_open())
		throw std::runtime_error("Error: cannot open config file");
	for (std::string line; std::getline(file, line);)
	{
		if (line_empty(line))
			continue ;
		if (!line.compare(0,7,"server:"))
			;
		else
			throw std::runtime_error("Error: invalid directive");
		
	}
}