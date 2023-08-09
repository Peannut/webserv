/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cgi.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoukaddo <zoukaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 13:33:27 by zoukaddo          #+#    #+#             */
/*   Updated: 2023/08/09 10:24:08 by zoukaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGI_HPP
#define CGI_HPP

#include "prototypes.hpp"

#define CGI_BUFFER 10

struct 	Cgi
{
	pid_t pid;
	char **env;
	std::string pathinfo;
	int	fd[2];
	int fd2[2];
	std::vector<char> body;
	std::vector<char> cgi_buffer;
	bool _isDone;
	Server _srv;
	Location loc;

	Cgi(): pid(-1), env(NULL), _isDone() {}
	~Cgi() {
		if (env)
		{
			int i = 0;
			while (env[i])
				delete env[i++];
			delete env;
		}
	}
};

#endif // ! CGI_HPP
