/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   web.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoukaddo <zoukaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 16:18:07 by zoukaddo          #+#    #+#             */
/*   Updated: 2023/07/04 16:28:48 by zoukaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __WEB_HPP__
#define __WEB_HPP__

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

#endif 