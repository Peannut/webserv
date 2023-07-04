/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_pars.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoukaddo <zoukaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 08:42:48 by zoukaddo          #+#    #+#             */
/*   Updated: 2023/07/04 23:40:09 by zoukaddo         ###   ########.fr       */
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

	std::vector<std::string> ip_split = split(host, '.');
	if (ip_split.size() != 4)
		throw std::runtime_error("Error: invalid ip address");
	for(int i = 0; i < 4; i++)
	{
		// int var = stringToLong(ip_split[i]);
		int var = std::stoi(ip_split[i]);
		if (var < 0 || var > 255)
			throw std::runtime_error("Error: invalid ip address");
		ip <<= 8;
		ip += var;
	}
	if (server.listen.first > 0)
		throw std::runtime_error("Error: listen already set");
	server.listen.first = ip;
}

void Web::setup_listen(std::string& line, server_block& server)
{
	std::string val = line.substr(8, line.size() - 8);
	if (line_empty(val))
		throw std::runtime_error("Error: listen does not have a value");
	std::vector<std::string> hostport = split(val, ':');
	std::cout << hostport.size() << std::endl;
	if (hostport.size() != 2)
		throw std::runtime_error("Error: invalid listen value");
	setup_host(hostport[0], server);
	size_t port = std::stoi(hostport[1]);
	server.listen.second = port;
	std::cout << server.listen.second << std::endl;
}

void Web::setup_servername(std::string& line, server_block& server)
{
	std::string val = line.substr(14, line.size() - 14);
	if (line_empty(val))
		throw std::runtime_error("Error: server_name does not have a value");
	if (!server.server_names.empty())
		throw std::runtime_error("Error: server_name already set");
	std::vector<std::string> names = split(val, ' ');
	server.server_names = names;
	std::cout << "server name: " << server.server_names[0] << std::endl;
}

void Web::setupClientbodySize(std::string& line, server_block& server)
{
	std::cout << "made it to client body size here" << std::endl;
	std::string val = line.substr(22, line.size() - 22);
	if (line_empty(val))
		throw(std::runtime_error("Error: error_page does not have a value"));
	std::vector<std::string> status = split(val, ' ');
	if (status.size() != 2)
		throw(std::runtime_error("Error: invalid error_page value"));
	std::pair<short, std::string> page;
	page.first = std::stoi(status[0]);
	if (page.first < 100 || page.first > 599)
		throw(std::runtime_error("Error: invalid error_page value"));
	else if (server.error_pages.find(page.first) != server.error_pages.end())
		throw(std::runtime_error("Error: error_page status already set"));
	page.second = status[1];
	server.error_pages.insert(page);
}

void Web::setupErrorPage(std::string& line, server_block& server)
{
	std::cout << "made it here" << std::endl;
	std::string val = line.substr(12, line.size() - 12);
	if (line_empty(val))
		throw std::runtime_error("Error: error_page does not have a value");
	std::vector<std::string> error = split(val, ' ');
	if (error.size() != 2)
		throw std::runtime_error("Error: invalid error_page value");
	int code = std::stoi(error[0]);
	if (code < 100 || code > 599)
		throw std::runtime_error("Error: invalid error_page value");
	server.error_pages[code] = error[1];
	std::cout << server.error_pages[code] << std::endl;
	
	// print the map error_pages
	std::cout << "map error_pages" << std::endl;
	for (std::map<short, std::string>::iterator it = server.error_pages.begin(); it != server.error_pages.end(); it++)
	{
		std::cout << it->first << " => " << it->second << '\n';
	}
	
}

void Web::setupServer(std::ifstream& file)
{
	server_block server;
	for (std::string line; std::getline(file, line);)
	{
		std::cout << line.compare(0,8,"\tlisten") << std::endl;
		if (line_empty(line))
			continue ;
		if (!line.compare(0,8,"\tlisten:"))
			setup_listen(line, server);
		else if (!line.compare(0, 13, "\tserver_name:"))
			setup_servername(line, server);
		else if (!line.compare(0, 18, "\tclient_body_size:"))
			setupClientbodySize(line, server);
		else if (!line.compare(0, 12,"\terror_page:"))
			setupErrorPage(line, server);
		else
			throw std::runtime_error("Error: invalid server directive hna");
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
			setupServer(file);
		else
			throw std::runtime_error("Error: invalid directive");
		
	}
}