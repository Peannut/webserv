#include "includes.hpp"

std::string buildErrorResponseB(const Request &request) {
	std::string response_Body;
	//get the file from  request structur and read it into a string;
	return response_Body;
}

std::string buildErrorResponseH(cont Request &request) {
	std::string headers;
	std::map<enum, std::string> errorCodes;
	errorCodes.insert(std::make_pair(0, " 400 Bad Request"));
	errorCodes.insert(std::make_pair(1, " 405 Method Not Allowed"));
	errorCodes.insert(std::make_pair(2, " 505 HTTP Version Not Supported"));
	errorCodes.insert(std::make_pair(3, " 411 Length Required"));

	headers += request._version;
	std::map<enum ,std::string>::iterator it = errorCodes.find(request._error);
	if (it != errorCodes.end()) {
		headers += it->second;
	}
	else {
		headers += " 501 Not Implemented";
	}
	headers += "\r\n" + "Content-Type: " + "text/html" + "\r\n";
	header += "Connection: Close" + "\r\n";
	headers += "Content-lenght: " + "\r\n\r\n";
	return headers;
}