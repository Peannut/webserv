/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserver.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoukaddo <zoukaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 08:33:43 by zoukaddo          #+#    #+#             */
/*   Updated: 2023/06/17 08:53:39 by zoukaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _WEBSERVER_HPP_
#define _WEBSERVER_HPP_

#include "../../webserv.hpp"


class Webserver
{
	private:
	std::vector<server_block> config;
		/* data */
	public:
		Webserver(/* args */);
		~Webserver();

		void setupconfig(const std::string& filename);
		void setupServer(std::ifstream& file);


};

Webserver::Webserver(/* args */)
{
}

Webserver::~Webserver()
{
}



#endif // !_WEBSERVER_HPP_
