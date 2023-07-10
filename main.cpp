#include "header.hpp"


// bool pathValid (const std::string &path) {
// 	if (path.substr(0, 7) != "http://") {
// 		std::cerr << "bad protocol" << std::endl;
// 		return false;
// 	}
// 	size_t slashpos = path.find('/', 7);
// 	if (slashpos == std::string::npos) {
// 		std::cerr << "no slash at the end of host" << std::endl;
// 		return false;
// 	}
// 	std::string host = path.substr(7, slashpos - 7);
// 	if (host.find('.')  == std::string::npos) {
// 		return false;
// 	}
// 	return true;
// }

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

metaResponse generateResponse(const metaRequest &request) {
	metaResponse response;

	if (request._method == "GET") {
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
					else {

					}
				}
				else {//resource is a file

				}
			}
			else { //requestedRerousce does not exist
				response.statusCode = 404;
				response.statusMessage = "Not Found";
			}
	} 
	return response;
}


int main (int ac, char **av) {

	metaRequest parsedreq;

	parsedreq._method = "GET";
	parsedreq._path = "http://friw.com/file.html";
    parsedreq._version = "HTTP/1.1";
    parsedreq._headers.push_back(std::make_pair("contet-Type", "application/json"));
    parsedreq._body = "Request body";

	// std::cout << getContentType(parsedreq._path)<< std::endl;
	// std::cout << readResource("Makefile") << std::endl;
	metaResponse response = generateResponse(parsedreq);

	//serve the response;

	return 0;
}
