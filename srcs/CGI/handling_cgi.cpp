/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_cgi.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoukaddo <zoukaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 12:24:22 by zoukaddo          #+#    #+#             */
/*   Updated: 2023/08/12 23:29:46 by zoukaddo         ###   ########.fr       */
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
        std::cout << file.loc->cgi_bin.second.c_str() << std::endl;
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

    if (env_maker(file) == 1)
        return (1);
    pipe(_cgi.fd);
    // pipe(_cgi.fd2);
    std::cout << "pipe done" << std::endl;
    return (0);
}

void Response::data_reader()
{
    char buffer[CGI_BUFFER + 1];
    int bytes_read;

    // Read data from the CGI pipe until there's no more data
    while ((bytes_read = read(_cgi.fd[0], buffer, CGI_BUFFER)) > 0)
    {
        // Null-terminate the buffer after reading data
        buffer[bytes_read] = '\0';

        // Append the read data to the cgi_buffer
        _cgi.cgi_buffer.insert(_cgi.cgi_buffer.end(), buffer, buffer + bytes_read);
    }

    if (bytes_read == 0)
    {
        // No more data to read, close the read end of the pipe
        close(_cgi.fd[0]);

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

void Response::reqbodysend()
{
    size_t content_length = 0;

    std::map<std::string, std::string>::iterator it = request->_fields.find("CONTENT-LENGTH");
    if (it != request->_fields.end())
        content_length = std::atoi(it->second.c_str());
        // copy request body to _cgi.body
    std::cout << "upload file sizeeee" << request->_body.size() << std::endl;
        for(size_t i = 0; i < request->_body.size(); i++)
            _cgi.body.push_back(request->_body[i]);

    size_t read_size = 0;
    size_t write_size = 0;
    while (read_size < content_length)
    {
        // Calculate the remaining bytes to write
        size_t remaining_bytes = content_length - read_size;

        // Calculate the size to write in this iteration
        if (_cgi.body.size() > CGI_BUFFER) write_size = remaining_bytes < CGI_BUFFER ? remaining_bytes : CGI_BUFFER;
        else write_size = remaining_bytes < _cgi.body.size() ? remaining_bytes : _cgi.body.size();

        // if (_cgi.body.size() > CGI_BUFFER)
        //     write_size = std::min(remaining_bytes, static_cast<size_t>(CGI_BUFFER));
        // else
        //     write_size = std::min(remaining_bytes, static_cast<size_t>(_cgi.body.size()));

        // Write data to the pipe
        // std::cout << "cgi body before write: " << std::string(_cgi.body.data(), _cgi.body.size()) << std::endl;
        ssize_t bytes_written = write(_cgi.fd[1], _cgi.body.data(), write_size);
        if (bytes_written == -1)
            break;
        else if (bytes_written == 0)
            break;

        _cgi.body.erase(_cgi.body.begin(), _cgi.body.begin() + bytes_written);
        //  std::cout << "cgi body after write: " << std::string(_cgi.body.data(), _cgi.body.size()) << std::endl;
        // Update the read size
        read_size += bytes_written;
        // Break if the read size reaches the content length
        if (read_size >= content_length)
            break;
    }

    // Close the write end of the pipe, signaling the end of data
    close(_cgi.fd[1]);
}

void Response::cgi_execve(File &file)
{
    _cgi.pid = fork();
    std::cout << "leeee piiiid" << _cgi.pid << std::endl;
    
    if (_cgi.pid == -1) {
        perror("fork");
        exit(1);
    }
    if (_cgi.pid == 0) { // Child process
        // Close unused file descriptors
        // close(_cgi.fd[1]); // Close write end of the pipe
        // close(_cgi.fd2[0]); // Close read end of the second pipe
        std::cerr << "chiiiiiiiiiiiiiiild process" << std::endl;
        // Redirect standard input and standard output
        
        // if post method and upload file dupe2 to file insted of _cgi.fd[0]

        if (dup2(_cgi.fd[0], STDIN_FILENO) == -1) {
            perror("dup2");
            exit(1);
        }
        std::cerr << "&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&" << std::endl;
        if (dup2(_cgi.fd[1], STDOUT_FILENO) == -1) {
            perror("dup2");
            exit(1);
        }
        std::cerr << "chiiiiiiiiiiiiiiild process 22222" << std::endl;

        // Close the remaining file descriptors in the child process
        // close(_cgi.fd[0]);
        // close(_cgi.fd2[1]);

        // Set up arguments for execve
     // Set up arguments for execve
        std::string filepath = *file.fullpath;
        char * av[3];
        av[0] = new char[file.loc->cgi_bin.second.length()];
        av[1] = new char[filepath.length()];
        av[2] = NULL;
        std::strcpy(av[0], file.loc->cgi_bin.second.c_str());
        std::strcpy(av[1], filepath.c_str());
        // Execute the CGI script
        if (execve(av[0], av, _cgi.env) == -1) {
            std::cerr << "errrrrrrrrror" << std::endl;
            perror("execve");
            std::cerr << "***********93333333333333333999999999999" << std::endl;
            exit(1);
        }
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

    // // Split message into headers and body
    // size_t pos = _message.find("\r\n\r\n");
    // std::string _message_body = _message.substr(pos + 4);
    // std::string headers = _message.substr(0, pos + 4);

    // // Check if "Content-length: " exists
    // size_t content_length_pos = headers.find("Content-length: ");
    // if (content_length_pos == std::string::npos)
    // {
    //     // If "Content-length: " does not exist, calculate the content length dynamically
    //     size_t calculated_content_length = _message_body.length();

    //     // Append the "Content-length" header before the end of headers
    //     size_t end_of_headers_pos = headers.find_last_not_of("\r\n");
    //     headers.insert(end_of_headers_pos + 1, "\r\nContent-length: " + std::to_string(calculated_content_length));
    // }

    // // Update the modified CGI output (_message)
    // _message = headers + _message_body;

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
    else if (err == -1)
    {
        if ((WIFEXITED(status) && WEXITSTATUS(status) == EXIT_FAILURE))
            serveDefaultErrorPage();
        perror("waitpid");
        std::cout << "errrr " << err << "   /" << WEXITSTATUS(status)<< std::endl;
        std::cout << "((((((((((((((((((((((((((((((()))))))))))))))))))))))))))))))" << std::endl;
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
	std::cout << "size cgiii" << size << std::endl;
	_cgi.env = new char*[size+ 9]();
	
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
    _cgi.env[i++] = strdup(("SCRIPT_NAME=" + fullpath).c_str());
    _cgi.env[i++] = strdup(("PATH_INFO=" + fullpath).c_str());
    _cgi.env[i++] = strdup(("QUERY_STRING=" + request->_query).c_str());
    _cgi.env[i++] = strdup(("REQUEST_URI=" + file.uri).c_str());
    _cgi.env[i++] = strdup("REDIRECT_STATUS=200");
    _cgi.env[i++] = strdup(("REQUEST_METHOD="+ val).c_str());
    _cgi.env[i] = NULL;
    int sizo = i;
    std::cout << "the whole env" << std::endl;

    for (int i = 0; i < sizo ; i++)
    {
        if (_cgi.env[i] != NULL)
            std::cout << _cgi.env[i] << std::endl;
    }
    return (0);
}
