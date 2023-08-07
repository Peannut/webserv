#include "includes.hpp"

File::File(std::string *path, const std::string &reqUri, const Location *location) : fullpath(path), uri(reqUri),  loc(location) {
	setFileInformation();
}

bool File::fileExists() {
	return(access(fullpath->c_str(), F_OK) == 0);
}

bool File::isDirectory() {
	return (access(fullpath->c_str(), X_OK) == 0);
}

bool File::nameHasSlash() {
	size_t lastChar = fullpath->length() - 1;
	return (fullpath->at(lastChar) == '/');
}

void	File::extractFileName() {
	size_t lastSlash = uri.find_last_of('/');
	if (lastSlash == uri.length() - 1) {//slash mamorah walou
		if (lastSlash == 0) { //makayn walou 7ta 9bel slash
			filename = "/";
			return;
		}
		lastSlash = uri.find_last_of('/', uri.length() - 2);
	}
	filename = uri.substr(lastSlash + 1, uri.length() - lastSlash);
}

void	File::extractExtention() {
	size_t dot = filename.find_last_of('.');
	size_t nameLenght = filename.length();
	if (dot == std::string::npos) {
		extention = "N/A";
		return;
	}
	if (nameHasSlash()) {
		nameLenght -= 1;
	}
	extention = filename.substr(dot, nameLenght - dot);
}

void	File::separatePathInfo() {
	size_t pos = fullpath->find_last_of(filename);
	pathInfo = fullpath->substr(pos + 1, fullpath->length() - pos);
}

bool	File::concatinateIndexFile() {
    for (std::vector<std::string>::const_iterator it = loc->index.begin(); it != loc->index.end(); ++it) {
        std::string path = (*fullpath) +  *it;
		// std::cout << " ----------path after concatinating is: " << path << "------------" << std::endl;
        if (!access(path.c_str(), F_OK)) {
            (*fullpath) += *it;
			uri += *it;
			return true;
        }
    }
	return false;
}

bool	File::fileCgiSupport() {
	if (!existing || (directory && !endWithSlash)) {
		// std::cout << "*******dkhel l if ghalta f cgi support******* " << std::endl;
		return false;
	}
	return (loc->cgi_bin.first == extention);
}

void	File::setFileInformation() {
	existing = fileExists();
	directory = isDirectory();
	endWithSlash = nameHasSlash();
	if (directory && endWithSlash) {
		indexFound = concatinateIndexFile();
	}
	extractFileName();
	extractExtention();
	cgi = fileCgiSupport();
	separatePathInfo();
	/*std::cout << "--file existance: " << existing << "--is resource directory: " << directory << std::endl << \
	 "--does path has slash at the end: " << endWithSlash << "--file fullpath :"  \
	 << *fullpath << std::endl <<  "--file uri: " << uri << \
	 "--file extention: "<< extention <<"--file supports CGI: " << cgi << std::endl;*/
}