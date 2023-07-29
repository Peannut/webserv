/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_cgi.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoukaddo <zoukaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 12:24:22 by zoukaddo          #+#    #+#             */
/*   Updated: 2023/07/28 16:16:29 by zoukaddo         ###   ########.fr       */
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


void Response::cgi_execve(const Location &loc)
{
    _cgi.pid = fork();
    if (_cgi.pid == 0)
    {
        dup2(_cgi.fd2[0], 0);
        dup2(_cgi.fd[1], 1);
        
        close(_cgi.fd[1]);
        close(_cgi.fd[0]);

        close(_cgi.fd2[1]);
        close(_cgi.fd2[0]);

        const char* script_path_cstr = loc.cgi_bin.second.c_str();
        const_cast<char *>(script_path_cstr);
        // I should execve locationpath d cgi dl config
         char *const argv[] = {
            script_path_cstr,
            NULL

        };
        // execve(loc.cgi_bin.second.c_str(), );
        // exit(42);
    }
    close(_cgi.fd[1]);
    close(_cgi.fd2[0]); 
}

void Response::cgiResponse(void)
{
    

}


// std::string extract_path_info(const std::string& full_path) {
//     std::size_t first_dot_pos = full_path.find('.');
//     if (first_dot_pos != std::string::npos) {
//         // Find the next occurrence of '/' after the first dot
//         std::size_t next_slash_pos = full_path.find('/', first_dot_pos);
//         std::size_t query_pos = full_path.find('?', first_dot_pos);

//         if (next_slash_pos <= query_pos)
//             return full_path.substr(next_slash_pos, query_pos - next_slash_pos);
//     }

//     // If the dot or slash is not found, or the next slash is not present, or '?' appears before the next slash, return an empty string
//     return "/";
// }

std::string extract_path_info(const std::string& full_path) {
    std::size_t first_dot_pos = full_path.find('.');
    if (first_dot_pos != std::string::npos) {
        // Find the next occurrence of '/' after the first dot
        std::size_t next_slash_pos = full_path.find('/', first_dot_pos);
        std::size_t query_pos = full_path.find('?', first_dot_pos);

        if (query_pos != std::string::npos && next_slash_pos > query_pos) {
            // If a '?' appears before the next slash, return the substring between next_slash_pos and query_pos
            return full_path.substr(next_slash_pos, query_pos - next_slash_pos);
        } else if (next_slash_pos != std::string::npos) {
            // If there is no '?', extract the path_info from the string between first_dot_pos and next_slash_pos
            return full_path.substr(next_slash_pos,  query_pos - next_slash_pos);
        }
    }

    // If the dot or slash is not found, or the next slash is not present, or '?' does not appear before the next slash, return an empty string
    return "/";
}

// make function to setup the cgi environment
void Response::env_maker()
{
    std::cout << "hello" << std::endl;
	
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
    _cgi.pathinfo = extract_path_info(request->_path);
	_cgi.env[i++] = strdup(("PATH_INFO=" + _cgi.pathinfo).c_str());
    // ask about this
    // std::string full_path = "/home/peanut/webserv/srcs/Response/DefaultError/test.py/folder/next?a=x";

    // std::string r = extract_path_info(full_path);
    // std::cout << "rrrrrrrr:" <<r << std::endl;
    Methods method = request->get_method();
    std::string val;
    switch (method) {
    case GET_method:
        val = "GET";
        break;
    case POST_method:
        val = "POST";
        break;
    case DELETE_method:
        val = "DELETE";
    default :
        break;
    }
    _cgi.env[i++] = strdup(("REQUEST_METHOD="+ val).c_str());
    int sizo = i;
    for (int i = 0; i < sizo ; i++)
    {
        if (_cgi.env[i] != nullptr)
        {
            std::cout << _cgi.env[i] << std::endl;
        }
    }
    std::cout << "path d yassin:" << pathinformation << std::endl;
}