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
	std::ifstream file("DefaultError"); //mal9inach error page li me7tajin so kanservi default
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

void servingFileGet(Response *response ,const Server &server, const Location *loc, const std::string &loc_Path) {
	std::string fullpath;
	fullpath = resourceExists(response->request->_path);
	if (!fullpath.empty()) { //file found
		if (!isDirectory(fullpath)) { //resource is a file
			if (!fileCgi(fullpath, loc)) {//file has no cgi => serve it;
				//serve file OK 200;
			}
			else {//file has cgi
				//peanut part
			}
		}
		else { //resouce is a directory

		}
	}
	else { //file not found serve the not found page 404;
	}
}
