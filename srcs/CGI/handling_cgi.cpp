/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_cgi.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwina <zwina@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 12:24:22 by zoukaddo          #+#    #+#             */
/*   Updated: 2023/08/13 11:29:35 by zwina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.hpp"

std::string CGIENV_FORMAT(const std::string& str)
{
    std::string result = str;

    if (result != "CONTENT-TYPE" && result != "CONTENT-LENGTH")
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

int Response::handleCGI(File &file)
{   
    if (access(file.loc->cgi_bin.second.c_str(), X_OK))
    {
        serveErrorPage(*srv, 500, "Internal Server Error");
        return (1);
    }
    if (access(file.fullpath->c_str(), R_OK))
    {
        serveErrorPage(*srv, 404, "Not Found");
        return (1);
    }

    if (env_maker(file) == 1)
        return (1);
    pipe(_cgi.fd);
    return (0);
}

void Response::data_reader()
{
    char buffer[CGI_BUFFER + 1];
    int bytes_read;

    // Read data from the CGI pipe until there's no more data
    while ((bytes_read = read(_cgi.fd[0], buffer, CGI_BUFFER)) > 0)
    {
        buffer[bytes_read] = '\0';
        // Append the read data to the cgi_buffer
        _cgi.cgi_buffer.insert(_cgi.cgi_buffer.end(), buffer, buffer + bytes_read);
    }
    if (bytes_read == 0)
    {
        close(_cgi.fd[0]);
        return;
    }
    else if (bytes_read == -1)
    {
        perror("read");
        return;
    }
}

void Response::reqbodysend()
{
    size_t content_length = 0;

    std::map<std::string, std::string>::iterator it = request->_fields.find("CONTENT-LENGTH");
    if (it != request->_fields.end())
        content_length = std::atoi(it->second.c_str());
        
    for(size_t i = 0; i < request->_body.size(); i++)
        _cgi.body.push_back(request->_body[i]);

    size_t read_size = 0;
    size_t write_size = 0;
    while (read_size < content_length)
    {
        // Calculate the remaining bytes to write
        size_t remaining_bytes = content_length - read_size;

        // Calculate the size to write in this iteration
        if (_cgi.body.size() > CGI_BUFFER)
            write_size = remaining_bytes < CGI_BUFFER ? remaining_bytes : CGI_BUFFER;
        else
            write_size = remaining_bytes < _cgi.body.size() ? remaining_bytes : _cgi.body.size();

        ssize_t bytes_written = write(_cgi.fd[1], _cgi.body.data(), write_size);
        if (bytes_written == -1)
            break;
        else if (bytes_written == 0)
            break;

        _cgi.body.erase(_cgi.body.begin(), _cgi.body.begin() + bytes_written);
        read_size += bytes_written;
        // Break if the read size reaches the content length
        if (read_size >= content_length)
            break;
    }
    close(_cgi.fd[1]);
}

int Response::cgi_execve(File &file)
{
    _cgi.pid = fork();
    std::cout << "leeee piiiid" << _cgi.pid << std::endl;
    
    if (_cgi.pid == -1) {
        serveErrorPage(*srv, 500, "Internal Server Error");
        return 1;
    }
    if (_cgi.pid == 0) {
        if (dup2(_cgi.fd[0], STDIN_FILENO) == -1) {
            perror("dup2");
            std::exit(1);
        }
        if (dup2(_cgi.fd[1], STDOUT_FILENO) == -1) {
            perror("dup2");
            std::exit(1);
        }
        std::string filepath = *file.fullpath;
        char * av[3];
        av[0] = new char[file.loc->cgi_bin.second.length()];
        av[1] = new char[filepath.length()];
        av[2] = NULL;
        std::strcpy(av[0], file.loc->cgi_bin.second.c_str());
        std::strcpy(av[1], filepath.c_str());
        // Execute the CGI script
        if (execve(av[0], av, _cgi.env) == -1) {
            perror("execve");
            std::exit(1);
        }
    }
    return 0;
}

void Response::cgiResponse(void)
{
    // Convert vector of char to a string
    _message.assign(_cgi.cgi_buffer.begin(), _cgi.cgi_buffer.end());

    // Find the position of "HTTP/1.1" in the buffer
    size_t http_pos = _message.find("HTTP/1.1");
    if (http_pos == std::string::npos)
    {
        size_t status_pos = _message.find("Status: ");
        if (status_pos != std::string::npos)
            _message.replace(status_pos, 8, "HTTP/1.1 ");
        else
            _message.insert(0, "HTTP/1.1 200 OK\r\n");
    }

    // Check if "\r\n\r\n" exists to separate headers and body
    if (_message.find("\r\n\r\n") == std::string::npos)
    {
        // If "\r\n\r\n" does not exist, add it after the last header
        size_t last_header_pos = _message.rfind("\r\n");
        if (last_header_pos != std::string::npos)
            _message.insert(last_header_pos + 2, "\r\n");
    }
    std::cout << "Modified CGI Output:\n" << _message << std::endl;
    _message_size = _message.length();
}



void Response::cgi_supervisor(File &file)
{
    if (!cgi_execve(file))
    {
        reqbodysend();
        cgi_wait();
    }
}

void Response::cgi_wait()
{
    int status;

    err = waitpid(_cgi.pid, &status, WNOHANG);
    if (err == 0)
        return;
    else if (err == -1)
    {
        if ((WIFEXITED(status) && WEXITSTATUS(status) == EXIT_FAILURE))
            serveErrorPage(*srv, 500, "Internal Server Error");
    }
    else if (err == _cgi.pid)
    {
        std::cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
        data_reader();
        cgiResponse(); 
    }
    _cgi._isDone = true;
}

// make function to setup the cgi environment
int Response::env_maker(File &file)
{
    std::cout << "hello env_maker" << std::endl;
	
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
        break;
    default :
        break;
    }
    if (val == "DELETE")
    {
        serveErrorPage(*srv, 501, "Not Implemented");
        return (1);
    }


    int size = request->_fields.size();
	_cgi.env = new char*[size+ 9]();
	
	int i = 0;
    std::map<std::string, std::string>::iterator it = request->_fields.begin();
	while( it != request->_fields.end())
	{
		
        _cgi.env[i] = new char[it->first.size() + it->second.size() + 7];
        std::string line = CGIENV_FORMAT(it->first) + "=" + it->second;
        std::strcpy(_cgi.env[i], line.c_str());
		it++;
		i++;
	}

    std::string fullpath = *file.fullpath;
    _cgi.env[i++] = strdup("SERVER_PROTOCOL=HTTP/1.1");
    _cgi.env[i++] = strdup(("SCRIPT_FILENAME=" + fullpath).c_str());
    _cgi.env[i++] = strdup(("SCRIPT_NAME=" + fullpath).c_str());
    _cgi.env[i++] = strdup(("PATH_INFO=" + fullpath).c_str());
    _cgi.env[i++] = strdup(("QUERY_STRING=" + request->_query).c_str());
    _cgi.env[i++] = strdup(("REQUEST_URI=" + file.uri).c_str());
    _cgi.env[i++] = strdup("REDIRECT_STATUS=200");
    _cgi.env[i++] = strdup(("REQUEST_METHOD="+ val).c_str());
    _cgi.env[i] = NULL;
    return (0);
}
