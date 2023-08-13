/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cgi.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwina <zwina@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 13:33:27 by zoukaddo          #+#    #+#             */
/*   Updated: 2023/08/13 10:58:46 by zwina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGI_HPP
#define CGI_HPP

#include "prototypes.hpp"

#define CGI_BUFFER 1024

struct 	Cgi
{
	pid_t pid;
	char **env;
	std::string pathinfo;
	int	fd[2];
	std::vector<char> body;
	std::vector<char> cgi_buffer;
	bool _isDone;

	Cgi(): pid(-1), env(NULL), _isDone() {}
	~Cgi() {
		if (env)
		{
			int i = 0;
			while (env[i])
				delete env[i++];
			delete[] env;
		}
	}
};

#endif // ! CGI_HPP
