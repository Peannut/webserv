/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwina <zwina@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 20:11:14 by zoukaddo          #+#    #+#             */
/*   Updated: 2023/08/13 10:58:39 by zwina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_HPP
#define CONFIG_HPP

#include "prototypes.hpp"

struct Config
{
	std::vector<Server> config;
	std::map<std::pair<int, short>, std::vector<Server*> > configMap;

	Server &get_server(const size_t & index);
	void setupconfig(const std::string& filename);
	void setup_host(std::string& host, Server& server);
	void setup_listen(std::string& line, Server& server);
	void setupServer(std::ifstream& file);
	void setup_servername(std::string& line, Server& server);
	void setupClientbodySize(std::string& line, Server& server);
	void setupErrorPage(std::string& line, Server& server);
	void setupLocation(std::ifstream& file, std::string& line, Server& server);
	void setuproot(std::string line, Location& location);
	void setupindex(std::string line, Location& location);
	void setupmethods(std::string line, Location& location);
	void setupredirect(std::string line, Location& location);
	void setupautoindex(std::string line, Location& location);
	void setupcgibin(std::string line, Location& location);
	void setupuploadpass(std::string line, Location& location);
	void fillConfig2();
};

#endif // CONFIG_HPP
