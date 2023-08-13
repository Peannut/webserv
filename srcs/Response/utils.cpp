#include "includes.hpp"

bool checkRequestError(const Response &response) {
	return response.request->_error;
}

bool hasSlashEnd(const std::string &path) {
	if(path.at(path.length() - 1) != '/') {
		return false;
	}
	return true;
}

bool resourceExists(const std::string &path) {
	return(access(path.c_str(), F_OK) == 0);
}

bool pathSupportUpload(Response *response, const Location *loc) {
	return (response->request->_path == loc->upload_pass);
}

bool outilsHasIndex( std::string *path, const Location *loc) {
    for (std::vector<std::string>::const_iterator it = loc->index.begin(); it != loc->index.end(); ++it) {
        std::string fullpath = *path + '/' +  *it;
        std::ifstream indexFile(fullpath.data());
        if (resourceExists(fullpath)) {
            *path = fullpath;
			// if extention is not cgi == false
			size_t dot = path->find_last_of('.');
			std::string extention= path->substr(dot, path->length() - dot);
			return extention == loc->cgi_bin.first;
        }
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
