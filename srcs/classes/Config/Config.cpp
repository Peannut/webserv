/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoukaddo <zoukaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 20:12:12 by zoukaddo          #+#    #+#             */
/*   Updated: 2023/07/10 20:12:13 by zoukaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "includes.hpp"

void Config::setup_host(std::string& host, Server& server)
{
	size_t ip = 0;

	std::vector<std::string> ip_split = split(host, '.');
	if (ip_split.size() != 4)
		throw std::runtime_error("Error: invalid ip address");
	int i = 0;
	while(i < 4)
	{
		int var = std::stoi(ip_split[i]);
		if (var < 0 || var > 255)
			throw std::runtime_error("Error: invalid ip address");
		ip <<= 8;
		ip += var;
		i++;
	}
	if (server.listen.first > 0)
		throw std::runtime_error("Error: listen already set");
	server.listen.first = ip;
	std::cout << "ip "<< server.listen.first << std::endl;

}

void Config::setup_listen(std::string& line, Server& server)
{
	std::string val = line.substr(8, line.size() - 8);
	if (line_empty(val))
		throw std::runtime_error("Error: listen does not have a value");
	std::vector<std::string> hostport = split(val, ':');
	if (hostport.size() != 2)
		throw std::runtime_error("Error: invalid listen value");
	setup_host(hostport[0], server);
	size_t port = std::stoi(hostport[1]);
	server.listen.second = port;
	std::cout << "port "<< server.listen.second << std::endl;
}

void Config::setup_servername(std::string& line, Server& server)
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

void Config::setupClientbodySize(std::string& line, Server& server)
{
	// std::cout << "made it to client body size here" << std::endl;
	std::string val = line.substr(18, line.size() - 18);
	if (line_empty(val))
		throw(std::runtime_error("Error: client_body_size does not have a value"));

	if (server.client_body_size)
		throw(std::runtime_error("Error: client_body_size already set"));
	std::vector<std::string> size = split(val, ':');
	if (size.size() != 1 || size[0][0] == '-')
		throw(std::runtime_error("Error: invalid client_body_size value"));
	server.client_body_size = std::stoi(size[0]);
}

void Config::setupErrorPage(std::string& line, Server& server)
{
	std::cout << "made it here" << std::endl;
	std::string val = line.substr(12, line.size() - 12);
	if (line_empty(val))
		throw std::runtime_error("Error: error_page does not have a value");
	std::vector<std::string> error = split(val, ':');
	if (error.size() != 2)
		throw std::runtime_error("Error: invalid error_page value");

	std::pair<short, std::string> page;
	page.first = std::stoi(error[0]);
	if (page.first < 100 || page.first > 599)
		throw std::runtime_error("Error: invalid error_page status");
	else if (server.error_pages.find(page.first) != server.error_pages.end())
		throw std::runtime_error("Error: error_page status already set");
	
	page.second = error[1];
	server.error_pages.insert(page);

	// print error pages
	std::map<short, std::string>::iterator it = server.error_pages.begin();
	while (it != server.error_pages.end())
	{
		std::cout << it->first << "=>" << it->second << std::endl;
		it++;
	}
	
}

void Config::setuproot(std::string line, Location& location)
{
	if (!location.root.empty())
		throw std::runtime_error("Error: root already set");
	std::string val = line.substr(7, line.size() - 7);
	if (line_empty(val))
		throw std::runtime_error("Error: root does not have a value");
	std::vector<std::string> root = split(val, ' ');
	if (root.size() != 1)
		throw std::runtime_error("Error: invalid root value");
	if (root[0][root[0].size() - 1] == '/')
		root[0] += '/';
	location.root = root[0];
	// print root
	std::cout << "root: " << location.root << std::endl;
	
}

void Config::setupindex(std::string line, Location& location)
{
	if (!location.index.empty())
		throw std::runtime_error("Error: index already set");
	std::string val = line.substr(8, line.size() - 8);
	if (line_empty(val))
		throw std::runtime_error("Error: index does not have a value");
	std::vector<std::string> index = split(val, ' ');
	location.index = index;
	// print index
	std::cout << "index: ";
	for (size_t i = 0; i < location.index.size(); i++)
		std::cout << location.index[i] << " ";
	std::cout << std::endl;
	std::cout << "index size: " << location.index.size() << std::endl;

}

void Config::setupmethods(std::string line, Location& location)
{
	if (!location.methods.empty())
		throw std::runtime_error("Error: methods already set");
	std::string val = line.substr(10, line.size() - 10);
	if (line_empty(val))
		throw std::runtime_error("Error: methods does not have a value");
	std::vector<std::string> methods = split(val, ' ');
	size_t i = 0;
	while (i < methods.size())
	{
		if (methods[i] == "GET" || methods[i] == "POST" || methods[i] == "DELETE")
		{
			location.methods.insert(methods[i]);
			i++;
		}
		else
			throw std::runtime_error("Error: invalid method");
	}
	// print methods
	std::cout << "methods: ";
	std::set<std::string>::iterator it = location.methods.begin();
	while (it != location.methods.end())
	{
		std::cout << *it << " ";
		it++;
	}
	std::cout << std::endl;
}

void	Config::setupredirect(std::string line, Location& location)
{
	std::string val = line.substr(9, line.size() - 9);
	if (line_empty(val))
		throw std::runtime_error("Error: redirect does not have a value");
	std::vector<std::string> redirect = split(val, ' ');
	if (redirect.size() != 2)
		throw std::runtime_error("Error: invalid redirect value");

	
	int status = std::stoi(redirect[0]);
	// idk status code range
	if (status < 300 || status > 600)
		throw std::runtime_error("Error: invalid redirect status");
	location.redirect.first = status;
	location.redirect.second = redirect[1];

	// print location.redirection.first << std::endl;
	std::cout << "redirect: " << location.redirect.first << " " << location.redirect.second << std::endl;
}

void Config::setupautoindex(std::string line, Location& location)
{
	std::string val = line.substr(12, line.size() - 12);
	if (line_empty(val))
		throw std::runtime_error("Error: autoindex does not have a value");
	std::vector<std::string> autoindex = split(val, ' ');
	if (autoindex.size() != 1)
		throw std::runtime_error("Error: invalid autoindex value");
	if (autoindex[0] == "on")
		location.autoindex = true;
	else if (autoindex[0] == "off")
		location.autoindex = false;
	else
		throw std::runtime_error("Error: invalid autoindex value");
	// print autoindex
	std::cout << "autoindex: " << std::boolalpha <<location.autoindex << std::endl;

}

void Config::setupLocation(std::ifstream& file, std::string& line, Server& server)
{
	std::string val = line.substr(10, line.size() - 10);
	if (line_empty(val))
		throw std::runtime_error("Error: location does not have a uri");
	std::vector<std::string> uri = split(val, ' ');
	if (uri.size() != 1)
		throw std::runtime_error("Error: invalid location uri");
	std::pair<std::string, Location> location;
	location.first = uri[0];
	// std::string linee;
	while (std::getline(file, line))
	{
		if (line_empty(line))
			continue ;
		if (!line.compare(0,7,"\t\troot:"))
			setuproot(line, location.second);
		else if (!line.compare(0,8,"\t\tindex:"))
			setupindex(line, location.second);
		else if (!line.compare(0, 10, "\t\tmethods:"))
			setupmethods(line, location.second);
		else if (!line.compare(0, 13, "\t\tcgi:"))
			;
		else if (!line.compare(0, 13, "\t\tupload:"))
			;
		else if (!line.compare(0,12,"\t\tautoindex:"))
			setupautoindex(line, location.second);
		else if (!line.compare(0,9,"\t\treturn:"))
			setupredirect(line, location.second);
		else if (!line.compare(0, 6, "\tclose"))
		{
			server.locations.insert(location);
			break ;
		}
		else
			throw std::runtime_error("Error: invalid location directive");
	}

}

void Config::setupServer(std::ifstream& file)
{
	Server server;
	for (std::string line; std::getline(file, line);)
	{
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
		else if (!line.compare(0,10,"\tlocation:"))
			setupLocation(file, line, server);
		else if (line == "close")
		{
			config.push_back(server);
			break;
		}
		else
			throw std::runtime_error("Error: invalid server directive hna");
	}
	
}

void	Config::setupconfig(const std::string& filename)
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