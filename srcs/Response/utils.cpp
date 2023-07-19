#include "includes.hpp"

bool checkRequestError(const Response &response) {
	return response.request->_error;
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
	struct stat buffer;

    return stat(path.c_str(), &buffer) == 0;
}

// std::string searchFile(const std::string& requestedPath, const std::map<std::string, std::string>& locationRoots) {
//     std::string filePath;

//     // Iterate over the locationRoots map
//     for (const auto& locationRoot : locationRoots) {
//         const std::string& location = locationRoot.first;
//         const std::string& root = locationRoot.second;

//         // Check if the requested path matches the location
//         if (requestedPath.find(location) == 0) {
//             // Construct the full file path by concatenating the root and requested path
//             filePath = root + requestedPath.substr(location.length());
            
//             std::ifstream file(filePath.c_str());
//             if (file) {
//                 // File exists
//                 file.close();
//                 break;
//             }
//         }
//     }

//     return filePath;
// }

bool	fileCgi(const std::string &fullpath, const Location *loc) {
	if (!loc->cgi_bin.first.empty()) {
		size_t lastdot = fullpath.find_last_of('.');
		if (lastdot == std::string::npos) {
			//la mal9ach l extention nchouf hna chnou ghandir.
			//probably default error page.
		}
		std::string conType = fullpath.substr(lastdot + 1, fullpath.length() - lastdot);
		return conType == loc->cgi_bin.first;
	}
	return false;
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
	Response response(&request);

	if (request._method == GET_method) {
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
	else if (request._method == POST_method) {

	}
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
