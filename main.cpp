#include "header.hpp"


bool pathValid (const std::string &path) {
	if (path.substr(0, 7) != "http://") {
		std::cerr << "bad protocol" << std::endl;
		return false;
	}
	size_t slashpos = path.find('/', 7);
	if (slashpos == std::string::npos) {
		std::cerr << "no slash at the end of host" << std::endl;
		return false;
	}
	std::string host = path.substr(7, slashpos - 7);
	if (host.find('.')  == std::string::npos) {
		return false;
	}
	return true;
}

bool resourceExists (const std::string &path) {
	std::ifstream file(path.c_str());
	return file.good();
}

std::string getContentType(const std::string path) {
	std::string conType;

	size_t lastSlash = path.find_last_of('.');
	conType = path.substr(lastSlash+ 1, path.length() - lastSlash);
	if (conType == "html" || conType == "htm") {
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

// readResource function

// metaResponse generateResponse(const metaRequest &request) {
// 	metaResponse response;

// 	if (request._method == "GET") {
// 		if (pathValid(request._path)) {
// 			if (resourceExists(request._path)) {
// 				response.contentType = getContentType(request._path);
// 				response.content = readResource(request._path);
// 				//generate response
// 			}
// 			else {
// 				response.statusCode = 404;
// 				response.statusMessage = "Not Found";
// 			}
// 		}
// 		else {
// 			response.statusCode = 400;
// 			response.statusMessage = "Bad Request";
// 		}
// 	}
// 	return response;
// }


int main (int ac, char **av) {

	metaRequest parsedreq;

	parsedreq._method = "GET";
	parsedreq._path = "http://friw.com/file.chi haja";
    parsedreq._version = "HTTP/1.1";
    parsedreq._headers.push_back(std::make_pair("contet-Type", "application/json"));
    parsedreq._body = "Request body";

	getContentType(parsedreq._path);
	// metaResponse response = generateResponse(parsedreq);

	//serve the request;

	return 0;
}
