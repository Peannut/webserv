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
	Server _srv;
	Location loc;


	Cgi(): pid(-1), env(NULL) {}
};

#endif // ! CGI_HPP
