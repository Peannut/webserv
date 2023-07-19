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
	std::ifstream file("DefaultErrorPage"); //mal9inach error page li me7tajin so kanservi default
	ss << file.rdbuf();
	response_Body = ss.str();
	return response_Body;
}

std::string buildErrorResponseH(const Response &response) {
	std::string headers;
	std::map<int,  std::string> errorCodes;
	errorCodes.insert(std::make_pair(0, " 400 Bad Request"));
	errorCodes.insert(std::make_pair(1, " 405 Method Not Allowed"));
	errorCodes.insert(std::make_pair(2, " 505 HTTP Version Not Supported"));
	errorCodes.insert(std::make_pair(3, " 411 Length Required"));

	headers += response.request->_version;
	std::map<int, std::string>::iterator it = errorCodes.find(response.request->_error);
	if (it != errorCodes.end()) {
		headers += it->second;
	}
	else {
		headers += " 501 Not Implemented";
	}
	headers +="\r\nContent-Type:  text/html\r\n";
	headers += "Connection: Close\r\n";
	headers += "Content-lenght: \r\n\r\n";
	return headers;
}

void    buildResponseHeaders(Response *response) {
	response->_message += "HTTP/1.1 ";
	response->_message += std::to_string(response->statusCode);
	response->_message += " ";
	response->_message += response->statusMessage;
	response->_message += "\r\nContent-Type: ";
	response->_message += response->contentType;
	response->_message += "\r\n Connection: Close\r\n Content-lenght : ";
	response->_message += std::to_string(response->contentLength);
	response->_message += "\r\n\r\n";
}

void servingFileGet(Response *response ,const Server &server, const Location *loc, const std::string &loc_Path) {
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
