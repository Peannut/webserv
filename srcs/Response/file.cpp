#include "includes.hpp"

File::File(std::string *path, const std::string &reqUri, const Location *location) : fullpath(path), uri(reqUri) , loc(location) {
	std::cout << "file constructor" << std::endl;
	extractFileName();
	separatePathInfo();
}

void	File::extractFileName() {
	
	size_t lastSlash = fullpath->find_last_of('/');
	if (lastSlash == fullpath->length() - 1) {//slash mamorah walou
		std::cout << "commo" << std::endl;
		if (lastSlash == 0) { //makayn walou 7ta 9bel slash
			filename = "/";
			return;
		}
		lastSlash = fullpath->find_last_of('/', fullpath->length() - 2);
	}
	filename = fullpath->substr(lastSlash + 1, fullpath->length() - lastSlash);
	std::cout << "file name is: " << filename << std::endl;
}

// void	File::extractExtention(size_t &dotindex) {
// 	extention = fullpath->substr(dotindex, )
// }

void	File::separatePathInfo() {
	size_t dotIndex = fullpath->find_last_of('.');
	if (dotIndex == std::string::npos) {
		pathWithoutInfo = *fullpath;
		pathInfo = "";
		extention = "";
		cgi = false;
		return;
	}
	// extractExtention(dotIndex);
	size_t closestSlash = fullpath->find_first_of('/', dotIndex);
	if (closestSlash == std::string::npos) {
		closestSlash = fullpath->length();
	}
	pathWithoutInfo = fullpath->substr(0, closestSlash + 1);
	pathInfo = fullpath->substr(closestSlash, fullpath->length() - closestSlash + 1);
	std::cout << "path to file is: *" << pathWithoutInfo<<"*" << std::endl << "path Info: *" << pathInfo << "*" <<std::endl;
}
