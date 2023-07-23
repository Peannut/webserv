#include "includes.hpp"

std::string findErrorPage(const Response &response,const Server &srv) {
	std::string response_Body;
	std::string errorPagePath;
	std::ostringstream ss;
	Server tmp = srv;
	std::map<short, std::string>::iterator it = tmp.error_pages.find(response.request->_error);
	if (it != tmp.error_pages.end()) { //error page path was found
		errorPagePath = it->second;
		std::ifstream file(errorPagePath.c_str());
		if (file) { //was able to open the error page file.
			ss << file.rdbuf();
			response_Body = ss.str();
		}
	}
	std::ifstream file("src/Response/DefaultErrorPage/index.html"); //mal9inach error page li me7tajin so kanservi default
	ss << file.rdbuf();
	response_Body = ss.str();
	return response_Body;
}

void	buildErrorResponse(const Server &server, Response *response) {
	std::map<short, std::string>::const_iterator it = server.error_pages.find(response->request->_error);
	if (it != server.error_pages.end()) {
		response->serveErrorPage(server, it->first, it->second);
		return;
	}
	response->serveDefaultErrorPage();
}

void    buildResponseHeaders(Response *response) {
	std::stringstream tmp;
	response->_message += "HTTP/1.1 ";
	tmp << response->statusCode;
	response->_message += tmp.str();
	response->_message += " ";
	response->_message += response->statusMessage;
	response->_message += "\r\nContent-Type: ";
	response->_message += response->contentType;
	response->_message += "\r\nConnection: Close\r\nContent-lenght: ";
	tmp.str("");
	tmp << response->contentLength;
	response->_message += tmp.str();
	response->_message += "\r\n\r\n";
	response->_message_size = response->_message.length();
}

void servingFileGet(Response *response ,const Server &server, const Location *loc, const std::string &loc_Path) {
	UNUSED(loc_Path);
	if (resourceExists(response->request->_path)) { //file does exists
		if (!isDirectory(response->request->_path)) { //resource is a file
			if (!fileCgi(response->request->_path, loc)) {//file has no cgi => serve it;
				response->fillBodyFile(server);
				response->getbodySize();
				buildResponseHeaders(response);
			}
			else {//file has cgi
				///////////////CGI/////////////////
			}
		}
		else { //file is a directory
			if (hasSlashEnd(response->request->_path)) {
				if (response->hasAutoIndex(loc)) { // check autoindex
					if (!fileCgi(response->request->_path, loc)) {
						response->fillBodyFile(server);
						response->getbodySize();
						buildResponseHeaders(response);
					}
					else {//file has cgi
						///////////////CGI/////////////////
					}
				}
				else { //no index should check autoindex here
					if (!loc->autoindex) {
						response->serveErrorPage(server, 403, "Forbidden");
					}
				}
			}
			else { // uri with no slash at the end
				response->serveErrorPage(server, 301, "Moved Permenantly");
				//will add redirection to uri with / at the end.
			}
		}
	}
	else { //file not found serve the not found page 404;
		response->serveErrorPage(server, 404, "Not Found");
	}
}

void    deletingFile(Response *response, const Server &server, const Location *loc) {
	if (resourceExists(response->request->_path)){
		if (!isDirectory(response->request->_path)) {
			if(!fileCgi(response->request->_path, loc)) {
				response->removeFile(server);
			}
			else {
				//////////////CGI//////////////
			}
		}
		else {//directory
			if (hasSlashEnd(response->request->_path)) {
				//chi haja machi tal tem f schema;
			}
			else { // makaynach slash
				response->serveErrorPage(server, 409, "Conflict");
			}
		}
	}
	else {
		response->serveErrorPage(server, 404, "Not Found");
	}
}
