/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   web.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoukaddo <zoukaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 11:05:16 by zoukaddo          #+#    #+#             */
/*   Updated: 2023/06/20 11:08:01 by zoukaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _WEBSERVER_HPP_
#define _WEBSERVER_HPP_
#include "webserv.hpp"
class Web
{
	private:
	std::vector<server_block> config;

	public:
		Web();
		~Web();

		void setupconfig(const std::string& filename);
		void setup_host(std::string& host, server_block& server);
		void setup_listen(std::string& line, server_block& server);
		void setupServer(std::ifstream& file);

};

Web::Web()
{
}

Web::~Web()
{
}



#endif // !_WEBSERVER_HPP_
