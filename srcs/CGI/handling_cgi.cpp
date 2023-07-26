/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_cgi.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoukaddo <zoukaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 12:24:22 by zoukaddo          #+#    #+#             */
/*   Updated: 2023/07/26 16:13:46 by zoukaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.hpp"

std::string CGIENV_FORMAT(const std::string& str)
{
    std::string result = str;

    if (result != "Content-Type" && result != "Content-Length")
        result.insert(0, "HTTP_");

    for (char& c : result)
    {
        if (c == '-')
            c = '_';
        else
            c = std::toupper(c);
    }
	
    return result;
}

int Response::handleCGI(void)
{   
    env_maker();
    pipe(_cgi.fd);
    pipe(_cgi.fd2);
    return (1);
}


void Response::cgi_execve(void)
{
    _cgi.pid = fork();
    if (!_cgi.pid)
    {
        dup2(_cgi.fd2[0], 0);
        dup2(_cgi.fd[1], 1);

        close(_cgi.fd[1]);
        close(_cgi.fd[0]);

        close(_cgi.fd2[1]);
        close(_cgi.fd2[0]);


        // I should execve locationpath d cgi dl config
        // execve();
        exit(42);
    }
    close(_cgi.fd[1]);
    close(_cgi.fd2[0]);
}

void Response::cgiResponse(void)
{
    

}

// make function to setup the cgi environment
void Response::env_maker()
{
	
    int size = request->_fields.size();
	std::cout << "size cgiii" << size << std::endl;
	_cgi.env = new char*[size+ 4]();
	
	int i = 0;
    std::map<std::string, std::string>::iterator it = request->_fields.begin();
	while( it != request->_fields.end())
	{
		
        _cgi.env[i] = new char[it->first.size() + it->second.size() + 7];
        std::string line = CGIENV_FORMAT(it->first) + "=" + it->second;
        std::copy(line.begin(), line.end(), _cgi.env[i]);
		it++;
		i++;
	}
    _cgi.env[i++] = strdup("SERVER_PROTOCOL=HTTP/1.1");
    _cgi.env[i++] = strdup(("PATH_INFO=" + _cgi.pathinfo).c_str());
    _cgi.env[i++] = strdup("REQUEST_METHOD=GET"); // static for now

    // ask about this
    // std::string val = static_cast<std::string>(_req->get_method());
    // _cgi.env[i++] = strdup(("REQUEST_METHOD="+ val).c_str());

    // print env

}