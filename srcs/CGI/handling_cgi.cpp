/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_cgi.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoukaddo <zoukaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 12:24:22 by zoukaddo          #+#    #+#             */
/*   Updated: 2023/08/02 19:45:31 by zoukaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.hpp"

std::string CGIENV_FORMAT(const std::string& str)
{
    std::string result = str;

    if (result != "Content-Type" && result != "Content-Length")
        result.insert(0, "HTTP_");

    for (size_t i = 0; i < result.length(); ++i)
    {
        char & c = result[i];
        if (c == '-')
            c = '_';
        else
            c = std::toupper(c);
    }
	
    return result;
}

int Response::handleCGI(void)
{   
    

    if (access(_cgi.loc.cgi_bin.second.c_str(), X_OK))
    {
        serveDefaultErrorPage();
        // 500
        // serveErrorPage(_cgi._srv, 404, "Not Found");
    }
    
    env_maker();
    pipe(_cgi.fd);
    pipe(_cgi.fd2);
    return (1);
}

void Response::data_reader(void)
{
    char buffer[CGI_BUFFER + 1];
    int bytes_read;
    std::string tmp;
    bytes_read = read(_cgi.fd[0], buffer, CGI_BUFFER);
    if (!bytes_read)
    {
        close(_cgi.fd[0]);
		// tmp = "Status: ";
        // error

        _cgi.counter += 1;
        return ;
    }
    _cgi.body.insert(_cgi.body.end(), buffer, buffer + bytes_read);
}

std::string Response::env_grabber(const std::string& key)
{
    std::string result;
    char** tmp_env = _cgi.env;
    while (*tmp_env)
    {
        std::string env_var = *tmp_env;
        if (env_var.find(key) == 0)
        {
            return (result = env_var.substr(key.size() + 1));
            break;
        }
        tmp_env++;
    }
    return NULL;
}

void    Response::reqbodysend(void)
{

    std::cout << "counter from reqbodysend: " << _cgi.counter << std::endl;
    // int content_length = std::stoi(env_grabber("CONTENT_LENGTH"));
    int content_length = std::stoi(request->_fields.find("Content-Length")->second);

    write(3,"testcgi\n",8);
    size_t read_size = 0;
    size_t write_size = 0;
    // print content_leght in error fd
    if (CGI_BUFFER < _cgi.body.size())
    {
           if (read_size + CGI_BUFFER > content_length)
            {
                write_size = content_length - read_size;
                write(_cgi.fd[1], &_cgi.body[0], write_size);
                _cgi.body.erase(_cgi.body.begin(), _cgi.body.begin() + write_size);
            }
            else
            {
                write(_cgi.fd[1], &_cgi.body[0], CGI_BUFFER);
                _cgi.body.erase(_cgi.body.begin(), _cgi.body.begin() + CGI_BUFFER);
            }
    }
    else
    {
        if (read_size + _cgi.body.size() > content_length)
        {
            write_size = content_length - read_size;
            write(_cgi.fd[1], &_cgi.body[0], write_size);
            _cgi.body.erase(_cgi.body.begin(), _cgi.body.begin() + write_size);
        }
        else
        {
            write(_cgi.fd[1], &_cgi.body[0], _cgi.body.size());
            _cgi.body.erase(_cgi.body.begin(), _cgi.body.begin() + _cgi.body.size());
        }
    }

    read_size += write_size;
    if (read_size == content_length || _cgi._srv.client_max_body_size == read_size)
    {
        close(_cgi.fd[1]);
        _cgi.body.clear();
        _cgi.counter++;
    }
}


void Response::cgi_execve(const Location &loc)
{
    _cgi.pid = fork();
    std::cout << "le pid:" << _cgi.pid << std::endl;
    if (!_cgi.pid)
    {
        std::cout << "here" << std::endl;
        dup2(_cgi.fd2[0], 0);
        dup2(_cgi.fd[1], 1);
        
        close(_cgi.fd[1]);
        close(_cgi.fd[0]);

        close(_cgi.fd2[1]);
        close(_cgi.fd2[0]);
       
        std::string filepath = _cgi.file_path;
        char * const av[3] = {
			const_cast<char * const>(loc.cgi_bin.second.c_str()),
			const_cast<char * const>(filepath.c_str()),
            NULL
		};
        
        if (execve(loc.cgi_bin.second.c_str(), av, _cgi.env) == -1)
        {
            std::cout << "execve failed" << std::endl;
            exit(1);
        }
    
    }
    close(_cgi.fd[1]);
    close(_cgi.fd2[0]);
    _cgi.counter++;
    std::cout << "counter:" << _cgi.counter << std::endl;
}

void Response::cgiResponse(void)
{
    // parse cgi output
    

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

// std::string extract_path_info(const std::string& full_path) {
//     std::size_t first_dot_pos = full_path.find('.');
//     if (first_dot_pos != std::string::npos) {
//         // Find the next occurrence of '/' after the first dot
//         std::size_t next_slash_pos = full_path.find('/', first_dot_pos);
//         std::size_t query_pos = full_path.find('?', first_dot_pos);

//         if (query_pos != std::string::npos && next_slash_pos > query_pos) {
//             // If a '?' appears before the next slash, return the substring between next_slash_pos and query_pos
//             return full_path.substr(next_slash_pos, query_pos - next_slash_pos);
//         } else if (next_slash_pos != std::string::npos) {
//             // If there is no '?', extract the path_info from the string between first_dot_pos and next_slash_pos
//             return full_path.substr(next_slash_pos,  query_pos - next_slash_pos);
//         }
//     }

//     // If the dot or slash is not found, or the next slash is not present, or '?' does not appear before the next slash, return an empty string
//     return "/";
// }


std::string get_filepath(const std::string &path)
{
    std::size_t first_dot_pos = path.find('.');
    if (first_dot_pos != std::string::npos) {
        // Find the next occurrence of '/' after the first dot
        std::size_t next_slash_pos = path.find('/', first_dot_pos);
        std::size_t query_pos = path.find('?', first_dot_pos);

        if (query_pos != std::string::npos && next_slash_pos > query_pos) {
            // If a '?' appears before the next slash, return the substring between next_slash_pos and query_pos
            return path.substr(0, query_pos);
        } else if (next_slash_pos != std::string::npos) {
            // If there is no '?', extract the path_info from the string between first_dot_pos and next_slash_pos
            return path.substr(0, next_slash_pos);
        }
    }

    // If the dot or slash is not found, or the next slash is not present, or '?' does not appear before the next slash, return an empty string
    return path;
}

std::string extract_file_path(const std::string &path)
{
    std::size_t first_dot_pos = path.find('.');
    if (first_dot_pos != std::string::npos) {
        // Find the next occurrence of '/' after the first dot
        std::size_t next_slash_pos = path.find('/', first_dot_pos);

        if (next_slash_pos != std::string::npos) {
            return path.substr(0, next_slash_pos);
        }
    }
    return path;
}

void Response::cgi_supervisor()
{
    std::cout << "supervisor" << std::endl;
    std::cout << "counter:" << _cgi.counter << std::endl;
	switch (_cgi.counter)
	{
		case 0:
			cgi_execve(_cgi.loc); 
			break;
		case 1:
            reqbodysend(); // send body to cgi;
			break;
		case 2:
			cgi_wait();// waitforcgi;
			break;
		case 3: 
			data_reader();// readfromcgi;
			break;
		case 4:
			// cgi response;
			break;
	}
}

void Response::cgi_wait()
{
    int status ;

    if (waitpid(_cgi.pid, &status, WNOHANG) == 0)
    {
        return ;
    }
    if (WEXITSTATUS(status) > 0)
        serveDefaultErrorPage();
    
    _cgi.counter += 1;
    return ;
}

// make function to setup the cgi environment
void Response::env_maker()
{
    std::cout << "hello" << std::endl;
	
    int size = request->_fields.size();
	std::cout << "size cgiii" << size << std::endl;
	_cgi.env = new char*[size+ 5]();
	
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
    // _cgi.pathinfo = extract_path_info(request->_path);
	_cgi.env[i++] = strdup("PATH_INFO=/");
    _cgi.env[i++] = strdup(("QUERY_STRING=" + request->_query).c_str());
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
    _cgi.file_path = get_filepath(request->_path);
    // std::cout << "file pathaaaaa:" << _cgi.file_path << std::endl;
    // std::cout << "path d zwina:" << request->_path << std::endl;
    std::cout << "body jay mn zwina" <<request->_body << std::endl;
}
