#include "includes.hpp"

File::File(std::string *path, const std::string &reqUri, const Location *location) : fullpath(path), uri(reqUri) , loc(location) {
	isDirectory();
	extractFileName();
	nameHasSlash();
	extractExtention();
	separatePathInfo();
}

bool File::isDirectory() {
	return (access(fullpath->c_str(), X_OK) == 0);
}

void	File::extractFileName() {
	size_t lastSlash = uri.find_last_of('/');
	if (lastSlash == uri.length() - 1) {//slash mamorah walou
		if (lastSlash == 0) { //makayn walou 7ta 9bel slash
			filename = "/";
			cgi = false;
			return;
		}
		lastSlash = uri.find_last_of('/', uri.length() - 2);
	}
	filename = uri.substr(lastSlash + 1, uri.length() - lastSlash);
}

bool File::nameHasSlash() {
	size_t lastChar = filename.length() - 1;
	return (filename.at(lastChar) == '/');
}

void	File::extractExtention() {
	size_t dot = filename.find_last_of('.');
	size_t nameLenght = filename.length();
	if (dot == std::string::npos) {
		extention = "N/A";
		cgi = false;
		return;
	}
	if (nameHasSlash()) {
		nameLenght -= 1;
	}
	extention = filename.substr(dot, nameLenght - dot);
	if (extention == loc->cgi_bin.first) {
		cgi = true;
	}
}

void	File::separatePathInfo() {
	size_t pos = fullpath->find_last_of(filename);
	pathInfo = fullpath->substr(pos + 1, fullpath->length() - pos);
}


