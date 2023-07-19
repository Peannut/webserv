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

Response::Response(Request *req)
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

    if (conType == "css") {
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
    return "text/html";
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

void    Response::serveDefaultErrorPage() {
    bodyFile.open("srcs/Response/DefaultError/index.html");
    setResponsefields(500, "Internal Server Error");
}

void	Response::serveErrorPage(const Server &srv, const short &errCode, const std::string &statMessage) {
	std::map<short, std::string>::const_iterator it = srv.error_pages.find(errCode);
        if(it == srv.error_pages.end()) {
            serveDefaultErrorPage();
            return;
        }
        bodyFile.open(it->second);
        setResponsefields(errCode, statMessage);
}

void Response::fillBodyFile( const Server &server ) { //khas server maydouzch liya const
    bodyFile.open(request->_path);

    if (!bodyFile.is_open()) {
        std::map<short, std::string>::const_iterator it = server.error_pages.find(500);
        if(it == server.error_pages.end()) {
            serveDefaultErrorPage();
            return;
        }
        bodyFile.open(it->second);
        setResponsefields(500, "Internal Server Error");
    }
    setResponsefields(200, "OK");
}

size_t Response::getbodySize( void ) {
    bodyFile.seekg(0, std::ios::end);
    std::streampos filesize = bodyFile.tellg();
    bodyFile.seekg(0);
    contentLength = static_cast<size_t>(filesize);
}

bool Response::hasAutoIndex( const Location *loc) {
    for (std::vector<std::string>::const_iterator it = loc->index.begin(); it != loc->index.end(); ++it) {
        std::string fullpath = request->_path + *it;
        std::ifstream indexFile(fullpath);
        if (resourceExists(fullpath)) {
            request->_path += *it;
            return true;
        }
    }
    return false;
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
        }
        // else if (this->request->_method == POST_method) {
            
        // }
        // else if (this->request->_method == DELETE_method) {

        // }
        // else{}
}
