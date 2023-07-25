#ifndef CGI_HPP
#define CGI_HPP

#include "prototypes.hpp"

struct Cgi{

	pid_t pid;
	char **env;
	std::string pathinfo;
	int	fd[2];
	int fd2[2];
};
#endif // ! CGI_HPP
