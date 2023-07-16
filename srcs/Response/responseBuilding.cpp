#include "includes.hpp"

std::string findErrorPage(const Request &response,Server &srv) {
	std::string response_Body;

	std::map<short, std::string>::iterator it = srv.error_pages.find(response._error);
	if (it != srv.error_pages.end()) {
		response_Body = it->second;
	}
	else {
		//serve the not found page
		//gotta get it's key from peanut
	}
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