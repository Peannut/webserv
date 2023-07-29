#include "includes.hpp"

File::File(std::string *path, const Location *location) : fullpath(path) , loc(location) {
	separatePathInfo();
}

void	File::separatePathInfo() {
	size_t dotIndex = fullpath->find_last_of('.');
	if (dotIndex == std::string::npos) {
		pathWithoutInfo = *fullpath;
		pathInfo = "";
		extention = "";
		cgi = false;
		return;
	}
	size_t closestSlash = fullpath->find_first_of('/', dotIndex);
	pathWithoutInfo = fullpath->substr(0, closestSlash + 1);
	pathInfo = fullpath->substr(closestSlash, fullpath->length() - closestSlash);
	std::cout << "path to file is: " << pathWithoutInfo << std::endl << "path Info: " << pathInfo <<std::endl;
}