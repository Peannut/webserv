#include "includes.hpp"

bool checkRequestError(const Request &request) {
	return request._mode._error != none_e;
}

bool isDirectory(const std::string &path) {
	struct stat pathStat;
	if (stat(path.c_str(), &pathStat) != 0) {
		std::cerr << "stat() error!" << std::endl;
		return false;
	} 
	return S_ISDIR(pathStat.st_mode);
}

bool hasSlashEnd(const std::string &path) {
	if(path.at(path.length() - 1) != '/') {
		return false;
	}
	return true;
}

bool resourceExists (const std::string &path) {
	std::ifstream file(path.c_str());
	return file.good();
}

std::string getContentType(const std::string &path) {
	std::string conType;

	size_t lastSlash = path.find_last_of('.');
	conType = path.substr(lastSlash+ 1, path.length() - lastSlash);

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

std::string readResource(const std::string &path) {
	std::string content;
	std::ifstream file(path.c_str(), std::ios::in | std::ios::binary);

	if(file) {
		file.seekg(0, std::ios::end);
		std::streampos lenght = file.tellg();
		file.seekg(0, std::ios::beg);
		
		content.resize(static_cast<size_t>(lenght));
		file.read(&content[0], lenght);

		file.close();
	}
	return content;
}

Response generateResponse(const Request &request) {
	Response response;

	if (request._method == get_method) {
		//check if client requested a dir or file
		if (isDirectory(request._path)) { // a directory is requested
			if (hasSlashEnd(request._path)) { //dir has '/' at the end
				//check if directory has indexfile (search for "index.html" in the dir) | if found serve it
				//if directory has no indexfile | check if autoindex is on
					// if on return autoindex of directory
					// else (autoindex off) return 403 Forbidden;
			}
			else { //dir does not have '/' at the end
				response.statusCode = 301;
				response.statusMessage = "Moved Pemanently";
			}
		}
		else { // a file is requested
			if (resourceExists(request._path)) {
				response.statusCode = 200;
				response.statusMessage = "OK";
				response.contentType = getContentType(request._path);
				response.content = readResource(request._path);
			}
			else {
				response.statusCode = 404;
				response.statusMessage = "Not Found";
			}
		}
	}
	// else if (request._method == "POST")
	else { //method == "DELETE"
		    if (resourceExists(request._path)) { // resource exists | now should check if it is a file or directory
				if (isDirectory(request._path)) { //resource is directory
					if(!hasSlashEnd(request._path)) { //not slash at the end
						response.statusCode = 409;
						response.statusMessage = "Conflict";
					}
					else { //has slash so we should check if it has cgi
						if ( /*has cgi*/1 ) {
							if (/*no index files*/1) {
								response.statusCode = 403;
								response.statusMessage = "Forbidden";
							}
							else /*has index files*/ {
								//si7r dyal cgi
							}
						}
						else /* no cgi */ { //delete all folder content
							if (/*delete was not succesfull*/1) {
								if( /*no write access on folder*/ 1) {
									response.statusCode = 403;
									response.statusMessage = "Forbidden";
								}
								else /*have write access*/ {
									response.statusCode = 500;
									response.statusMessage = "Internal Server Error";
								}
							}
							else /*delete succes*/ {
								response.statusCode = 204;
								response.statusMessage = "No Content";
							}
						}
					}
				}
				else {//resource is a file
					if (/*no cgi*/ 1) {
						//delete file function
						response.statusCode = 204;
						response.statusMessage = "No Content";
					}
					else /*has cgi*/ {
						//dak si7r dyal cgi
					}
				}
			}
			else { //requestedRerousce does not exist
				response.statusCode = 404;
				response.statusMessage = "Not Found";
			}
	} 
	return response;
}
