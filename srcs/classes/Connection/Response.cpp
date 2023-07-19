/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynuiga <ynuiga@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 15:03:17 by zwina             #+#    #+#             */
/*   Updated: 2023/07/11 11:11:36 by ynuiga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.hpp"

#include "includes.hpp"

Response::Response(const Request *req)
: request(req)
, _message_size()
, _offset()
{}

size_t Response::extract()
{
    size_t length = 0;
    while (length < BUFFER_SIZE)
    {
        if (_offset < _message_size) // sending message (the status line and the fileds in short)
            buffer[length] = _message[_offset];
        // sending body in a file;
        else if (!bodyFile.eof()) {
            bodyFile >> buffer[length];
        }
        else break; // nothing to send
        ++length;
        ++_offset;
    }
    return (length);
}

void Response::seek_back(const size_t & amount)
{
    size_t pos = bodyFile.tellg();
    bodyFile.seekg((pos <= amount)? 0 : pos - amount);
    _offset -= amount;
}

bool Response::is_done()
{
    return (_offset < _message_size && bodyFile.eof());
}

std::string Response::getContentType( void ) {
	std::string conType;

	size_t lastSlash = request->_path.find_last_of('.');
	conType = request->_path.substr(lastSlash+ 1, request->_path.length() - lastSlash);

	if (conType == "htm" || conType == "html") {
		return "text/html";
	}
	else if (conType == "css") {
		return "text/css";
	}
	else if (conType == "csv") {
		return "text/csv";
	}
	else if (conType == "gif") {
		return "image/gif";
	}
	else if (conType == "ico") {
		return "image/x-icon";
	}
	else if (conType == "jpeg" || conType == "jpg") {
		return "image/jpeg";
	}
	else if (conType == "js") {
		return "application/javascript";
	}
	else if (conType == "json") {
		return "application/json";
	}
	else if (conType == "png") {
		return "image/png";
	}
	else if (conType == "pdf") {
		return "application/pdf";
	}
	else if (conType == "svg") {
		return "image/svg+xml";
	}
	else if (conType == "txt") {
		return "text/plain";
	}
}

void Response::setStatusCode(const int &sc) {
    statusCode = sc;
}

void Response::setStatusMessage(const std::string &sm) {
    statusMessage = sm;
}

void Response::setContentType(const std::string &ct) {
    contentType = ct;
}

void Response::setContentlength(const size_t &cl) {
    contentLength = cl;
}

void Response::setResponsefields(const int &sc, const std::string &sm) {
    std::string ct;

    ct = getContentType();
    setStatusCode(sc);
    setStatusMessage(sm);
    setContentType(ct);
}

void Response::fillBodyFile( void ) {
    std::ifstream rdfile(request->_path);

    if (rdfile) {
        char c;
        while(rdfile.get(c)) {
            bodyFile.put(c);
        }
    }
    else {
        std::cerr << "error opening files!" << std::endl;
    }
    rdfile.close();
}

size_t Response::getbodySize( void ) {
    if (bodyFile.is_open()) {
        bodyFile.seekg(0, std::ios::end);
        std::streampos filesize = bodyFile.tellg();
        bodyFile.seekg(0);
        contentLength = static_cast<size_t>(filesize);
    }
    else{
        std::cerr << "error opening file!" << std::endl;
    }
}

void Response::serving(const Server &server, const Location *loc, const std::string &loc_Path) {

        if (checkRequestError(*this)) { //if request has an error;
                this->_message = buildErrorResponseH(*this);
                this->content = findErrorPage(*this, server);
                //after building now the Response header and body should start sending chunk by chunk to multiplexing;
        }
        //if request has no errors
        else if (this->request->_method == GET_method) { //first thing check if resourse is found in root if no error404 we pretend now it always exists
                servingFileGet(this ,server, loc, loc_Path);
        // if (isDirectory(response.request->_path)) { // a directory is requested
        //         if (hasSlashEnd(request._path)) { //dir has '/' at the end
        //                 //check if directory has indexfile (search for "index.html" in the dir) | if found serve it
        //                 //if directory has no indexfile | check if autoindex is on
        //                         // if on return autoindex of directory
        //                         // else (autoindex off) return 403 Forbidden;
        //         }
        //         else { //dir does not have '/' at the end
        //                 response.statusCode = 301;
        //                 response.statusMessage = "Moved Pemanently";
        //         }
        // }
        // else { // a file is requested
        //         if (resourceExists(request._path)) {
        //                 response.statusCode = 200;
        //                 response.statusMessage = "OK";
        //                 response.contentType = getContentType(request._path);
        //                 response.content = readResource(request._path);
        //                 }
        //         else {
        //                 response.statusCode = 404;
        //                 response.statusMessage = "Not Found";
        //                 }
        //         }
        }
        this->_message = getResponseHeaders(response, server, loc, loc_Path);
}
