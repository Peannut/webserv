/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoukaddo <zoukaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 20:12:12 by zoukaddo          #+#    #+#             */
/*   Updated: 2023/07/24 19:09:21 by zoukaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.hpp"

Server &Config::get_server(const size_t & index)
{
	return config[index];
}

void Config::setup_host(std::string& host, Server& server)
{
	size_t ip = 0;

	std::vector<std::string> ip_split = split(host, '.');
	if (ip_split.size() != 4)
		throw std::runtime_error("Error: invalid ip address");
	int i = 0;
	while(i < 4)
	{
		int var = std::atoi(ip_split[i].data());
		if (var < 0 || var > 255)
			throw std::runtime_error("Error: invalid ip address");
			
		ip <<= 8;
		ip += var;
		i++;
	}
	if (server.listen.first > 0)
		throw std::runtime_error("Error: listen already set");
	server.listen.first = ip;
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
	size_t port = std::atoi(hostport[1].data());
	server.listen.second = port;
	std::cout << "port function" << convertPortToString(server.listen.second) <<std::endl;
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
	std::string val = line.substr(22, line.size() - 22);
	if (line_empty(val))
		throw(std::runtime_error("Error: client_max_body_size does not have a value"));

	if (server.client_max_body_size)
		throw(std::runtime_error("Error: client_max_body_size already set"));
	std::vector<std::string> size = split(val, ':');
	if (size.size() != 1 || size[0][0] == '-')
		throw(std::runtime_error("Error: invalid client_max_body_size value"));
	server.client_max_body_size = std::atoi(size[0].data());
}

void Config::setupErrorPage(std::string& line, Server& server)
{
	std::string val = line.substr(12, line.size() - 12);
	if (line_empty(val))
		throw std::runtime_error("Error: error_page does not have a value");
	std::vector<std::string> error = split(val, ':');
	if (error.size() != 2)
		throw std::runtime_error("Error: invalid error_page value");

	std::pair<short, std::string> page;
	page.first = std::atoi(error[0].data());
	if (page.first < 100 || page.first > 599)
		throw std::runtime_error("Error: invalid error_page status");
	else if (server.error_pages.find(page.first) != server.error_pages.end())
		throw std::runtime_error("Error: error_page status already set");
	
	page.second = error[1];
	server.error_pages.insert(page);


	// print size of error pages
	std::cout << "size of error pages: " << server.error_pages.size() << std::endl;
	// print error pages
	std::map<short, std::string>::iterator it = server.error_pages.begin();
	while (it != server.error_pages.end())
	{
		std::cout << it->first << " here =>" << it->second << std::endl;
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

    if (!root[0].empty() && root[0][root[0].size() - 1] == '/')
    {
        root[0].pop_back(); // Remove the trailing slash '/'
    }

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

	
	int status = std::atoi(redirect[0].data());
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

void Config::setupcgibin(std::string line, Location& location)
{
	if (!location.cgi_bin.first.empty())
		throw (std::runtime_error("Error: cgi_bin duplication in value"));
	std::string val = line.substr(10, line.size() - 10);
	if (line_empty(val))
		throw std::runtime_error("Error: cgi_bin does not have a value");
	std::vector<std::string> cgi_bin = split(val, ' ');
	if (cgi_bin.size() != 2)
		throw std::runtime_error("Error: invalid cgi_bin value");
	location.cgi_bin.first = cgi_bin[0];
	location.cgi_bin.second = cgi_bin[1];
	if (location.cgi_bin.first != ".php" && location.cgi_bin.first != ".py")
		throw std::runtime_error("Error: invalid cgi_bin extension");
	// print cgi_bin
	std::cout << "cgi_bin: " << location.cgi_bin.first << " " << location.cgi_bin.second << std::endl;
}

void Config::setupuploadpass(std::string line, Location& location)
{
	std::string val = line.substr(14, line.size() - 14);
	if (line_empty(val))
		throw std::runtime_error("Error: upload_pass does not have a value");
	std::vector<std::string> upload_pass = split(val, ' ');
	if (upload_pass.size() != 1)
		throw std::runtime_error("Error: invalid upload_pass value");
	if(!location.upload_pass.empty())
		throw std::runtime_error("Error: upload_pass already set");
	location.upload_pass = upload_pass[0];
	// print upload_pass
	std::cout << "upload_pass: " << location.upload_pass << std::endl;

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
		else if (!line.compare(0, 10, "\t\tcgi-bin:"))
			setupcgibin(line, location.second);
		else if (!line.compare(0, 14, "\t\tupload_pass:"))
			setupuploadpass(line, location.second);
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

bool hasRootInServerfunc(const Server& server)
{
    if (!server.locations.empty())
    {
        const auto& lastLocationPair = *server.locations.rbegin();
        const Location& lastLocation = lastLocationPair.second;
        if (lastLocation.root.empty())
        {
            throw std::runtime_error("Error: Root not set for a location in the server");
        }
        return true;
    }
    return false;
}


void Config::setupServer(std::ifstream& file)
{
	Server server;
	bool hasRootInServer = false; // Flag to check if the server has at least one location with root
	bool location_exist = false;
	for (std::string line; std::getline(file, line);)
	{
		if (line_empty(line))
			continue ;
		if (!line.compare(0,8,"\tlisten:"))
			setup_listen(line, server);
		else if (!line.compare(0, 13, "\tserver_name:"))
			setup_servername(line, server);
		else if (!line.compare(0, 22, "\tclient_max_body_size:"))
			setupClientbodySize(line, server);
		else if (!line.compare(0, 12,"\terror_page:"))
			setupErrorPage(line, server);
		else if (!line.compare(0,10,"\tlocation:"))
		{
			location_exist = true;
			setupLocation(file, line, server);
			hasRootInServer = hasRootInServerfunc(server);
		}
		else if (line == "close")
		{
			 if (!hasRootInServer && location_exist)
            {
                throw std::runtime_error("Error: No location with root set in the server");
            }
			config.push_back(server);
			break;
		}
		else
			throw std::runtime_error("Error: invalid server directive hna");
	}
	
}

void Config::removeDuplicateServers()
{
    size_t i = 1;
    while (i < config.size())
    {
        const Server& currentServer = config[i];
        const Server& previousServer = config[i - 1];

        if (currentServer.listen == previousServer.listen)
        {
            if (!currentServer.server_names.empty() && !previousServer.server_names.empty() && currentServer.server_names[0] == previousServer.server_names[0])
            {
                // If same listen and server_name, keep the previous server and remove the current one
                config.erase(config.begin() + i);
            }
            else
            {
                // If same listen but different server_name, keep both servers
                i++;
            }
        }
        else
        {
            // If different listen values, keep the current server
            i++;
        }
    }
}


void	Config::setupconfig(const std::string& filename)
{
	// check file extension must be .conf
	if (filename.substr(filename.find_last_of(".") + 1) != "conf")
		throw std::runtime_error("Error: invalid config file extension must be .conf");
	std::ifstream file(filename.c_str());

	if (!file.is_open())
		throw std::runtime_error("Error: cannot open config file");
	for (std::string line; std::getline(file, line);)
	{
		if (line_empty(line))
			continue ;
		if (!line.compare(0,7,"server:"))
		{
			setupServer(file);
			
		}
		else
			throw std::runtime_error("Error: invalid directive");
		
	}
	// print config size
	// std::cout << "SIIIIIZE" << config.size() << std::endl;
	// print config
	file.close();
	removeDuplicateServers();
	// std::cout << "SIIIIIZE" << config.size() << std::endl;

	// for (const auto& server : config)
    // {
    //     std::cout << "Server:" << std::endl;
    //     std::cout << "\tListen: " << server.listen.first << "." << server.listen.second << std::endl;

    //     // Print other server properties as needed
	// 	for (const auto& errorPage : server.error_pages)
    //     {
    //         std::cout << "\t\tStatus Code: " << errorPage.first << "  File Path: " << errorPage.second << std::endl;
    //     }
    // }
}
