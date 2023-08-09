/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_cgi.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoukaddo <zoukaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 12:24:22 by zoukaddo          #+#    #+#             */
/*   Updated: 2023/08/09 17:22:54 by zoukaddo         ###   ########.fr       */
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
        serveDefaultErrorPage();
        std::cout << "500 t catcha" << std::endl;
        std::cout << "-&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&" << std::endl;
        return (1);
    }
    if (access(file.fullpath->c_str(), R_OK))
    {
        std::cout << file.fullpath->c_str() << std::endl;
        serveErrorPage(*srv, 404, "Not Found");
        std::cout << "404 t catcha" << std::endl;
        return (1);
    }
    env_maker(file);
    pipe(_cgi.fd);
    pipe(_cgi.fd2);
    std::cout << "pipe done" << std::endl;
    return (0);
}

void Response::data_reader()
{
    char buffer[CGI_BUFFER + 1];
    int bytes_read;

    // Read data from the CGI pipe until there's no more data
    while ((bytes_read = read(_cgi.fd2[0], buffer, CGI_BUFFER)) > 0)
    {
        // Null-terminate the buffer after reading data
        buffer[bytes_read] = '\0';

        // Append the read data to the cgi_buffer
        _cgi.cgi_buffer.insert(_cgi.cgi_buffer.end(), buffer, buffer + bytes_read);
    }

    if (bytes_read == 0)
    {
        // No more data to read, close the read end of the pipe
        close(_cgi.fd2[0]);

        // Handle the CGI output or response here, e.g., store it in a member variable, print it, or process it further.
        // _cgi.cgi_buffer.push_back('\0'); // Null-terminate the buffer
        std::cout << "CGI Output: " << _cgi.cgi_buffer.data() << std::endl;

        return;
    }
    else if (bytes_read == -1)
    {
        // Handle read error
        perror("read");
        // You can add error handling here
        return;
    }
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


void Response::reqbodysend()
{
    size_t content_length;
    
    std::map<std::string, std::string>::iterator it = request->_fields.find("CONTENT-LENGTH");
    if (it != request->_fields.end())
        content_length = std::stoi(it->second);
    else
        content_length = 0;

        
    std::cout << "content_length: from reqbody" << content_length << std::endl;

    // copy request body to _cgi.body
    for(size_t i = 0; i < request->_body.size(); i++)
        _cgi.body.push_back(request->_body[i]);


    size_t read_size = 0;
    ssize_t bytes_written = 0;
    while (read_size < content_length)
    {
        size_t write_size;
        if (_cgi.body.size() > CGI_BUFFER)
            write_size = std::min(static_cast<size_t>(CGI_BUFFER), content_length - read_size);
        else
            write_size = std::min(static_cast<size_t>(_cgi.body.size()), content_length - read_size);


        std::cout << "write_size: " << write_size << std::endl;
        bytes_written = write(_cgi.fd[1], _cgi.body.data(), write_size);
        std::cout << "cgi body: " << _cgi.body.data() << std::endl;
        if (bytes_written == -1)
            break;
        else if (bytes_written == 0)
            break;
        read_size += bytes_written;

        // Erase the written data from the buffer
        _cgi.body.erase(_cgi.body.begin(), _cgi.body.begin() + bytes_written);
    }

    // Close the write end of the pipe, signaling the end of data
    close(_cgi.fd[1]);
    close(_cgi.fd2[1]);
}

void Response::cgi_execve(File &file)
{
    _cgi.pid = fork();
    
    if (_cgi.pid == -1) {
        perror("fork");
        exit(1);
    }
    if (_cgi.pid == 0) { // Child process
        // Close unused file descriptors
        close(_cgi.fd[1]); // Close write end of the pipe
        close(_cgi.fd2[0]); // Close read end of the second pipe

        // Redirect standard input and standard output
        if (dup2(_cgi.fd2[1], STDOUT_FILENO) == -1) {
            perror("dup2");
            exit(1);
        }
        if (dup2(_cgi.fd[0], STDIN_FILENO) == -1) {
            perror("dup2");
            exit(1);
        }

        // Close the remaining file descriptors in the child process
        close(_cgi.fd[0]);
        close(_cgi.fd2[1]);

        // Set up arguments for execve
        std::string filepath = *file.fullpath;
        char * const av[3] = {
            const_cast<char * const>(file.loc->cgi_bin.second.c_str()),
            const_cast<char * const>(filepath.c_str()),
            NULL
        };
        // Execute the CGI script
        if (execve(file.loc->cgi_bin.second.c_str(), av, _cgi.env) == -1) {
            perror("execve");
            exit(1);
        }
    } 
    else { // Parent process
        // Close the unused ends of the pipes in the parent process
        close(_cgi.fd[0]);
        close(_cgi.fd2[1]);
    }
}

void Response::cgiResponse(void)
{
    // Convert vector of char to a string
    _message.assign(_cgi.cgi_buffer.begin(), _cgi.cgi_buffer.end());

    // Find the position of "HTTP/1.1" in the buffer
    size_t http_pos = _message.find("HTTP/1.1");

    // If "HTTP/1.1" is not found, replace "Status" with "HTTP/1.1 200 OK\r\n"
    if (http_pos == std::string::npos)
    {
        size_t status_pos = _message.find("Status: ");
        if (status_pos != std::string::npos)
        {
            // Replace only the "Status" with "HTTP/1.1"
            _message.replace(status_pos, 8, "HTTP/1.1 ");
        }
        else
        {
            // If "Status" is not found, add "HTTP/1.1 200 OK\r\n" at the beginning
            _message.insert(0, "HTTP/1.1 200 OK\r\n");
        }
    }

    // Check if "\r\n\r\n" exists to separate headers and body
    if (_message.find("\r\n\r\n") == std::string::npos)
    {
        // If "\r\n\r\n" does not exist, add it after the last header
        size_t last_header_pos = _message.rfind("\r\n");
        if (last_header_pos != std::string::npos)
            _message.insert(last_header_pos + 2, "\r\n");
    }

    // Split message into headers and body
    size_t pos = _message.find("\r\n\r\n");
    std::string _message_body = _message.substr(pos + 4);
    std::string headers = _message.substr(0, pos + 4);

    // Check if "Content-length: " exists
    size_t content_length_pos = headers.find("Content-length: ");
    if (content_length_pos == std::string::npos)
    {
        // If "Content-length: " does not exist, calculate the content length dynamically
        size_t calculated_content_length = _message_body.length();

        // Append the "Content-length" header before the end of headers
        size_t end_of_headers_pos = headers.find_last_not_of("\r\n");
        headers.insert(end_of_headers_pos + 1, "\r\nContent-length: " + std::to_string(calculated_content_length));
    }

    // Update the modified CGI output (_message)
    _message = headers + _message_body;

    // Print or store the modified CGI output
    std::cout << "Modified CGI Output:\n" << _message << std::endl;
    _message_size = _message.length();
}



void Response::cgi_supervisor(File &file)
{
    std::cout << "supervisor" << std::endl;

    cgi_execve(file);
    reqbodysend();
    cgi_wait();
}

void Response::cgi_wait()
{
    int status;

    err = waitpid(_cgi.pid, &status, WNOHANG);
    if (err == 0)
        return;
    else if (err == -1 || WEXITSTATUS(status) > 0)
        serveDefaultErrorPage();
    else if (err == _cgi.pid)
    {
        std::cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
        data_reader();
        cgiResponse(); 
    }
    _cgi._isDone = true;
}

// make function to setup the cgi environment
void Response::env_maker(File &file)
{
    std::cout << "hello env_maker" << std::endl;
	
    int size = request->_fields.size();
	std::cout << "size cgiii" << size << std::endl;
	_cgi.env = new char*[size+ 7]();
	
	int i = 0;
    std::map<std::string, std::string>::iterator it = request->_fields.begin();
	while( it != request->_fields.end())
	{
		
        _cgi.env[i] = new char[it->first.size() + it->second.size() + 7];
        std::string line = CGIENV_FORMAT(it->first) + "=" + it->second;
        std::strcpy(_cgi.env[i], line.c_str());
        // std::copy(line.begin(), line.end(), _cgi.env[i]);
		it++;
		i++;
	}

    std::string fullpath = *file.fullpath;
    _cgi.env[i++] = strdup("SERVER_PROTOCOL=HTTP/1.1");
    _cgi.env[i++] = strdup(("SCRIPT_FILENAME=" + fullpath).c_str());
    _cgi.env[i++] = strdup(("PATH_INFO=" + fullpath).c_str());
    _cgi.env[i++] = strdup(("QUERY_STRING=" + request->_query).c_str());
    _cgi.env[i++] = strdup(("REQUEST_URI=" + file.uri).c_str());

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
    _cgi.env[i] = NULL;
    int sizo = i;
    std::cout << "the whole env" << std::endl;

    for (int i = 0; i < sizo ; i++)
    {
        if (_cgi.env[i] != nullptr)
            std::cout << _cgi.env[i] << std::endl;
    }
}
