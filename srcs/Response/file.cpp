#include "includes.hpp"

File::File(std::string *path, const std::string &reqUri, const Location *location) : fullpath(path), uri(reqUri),  loc(location) {
	setFileInformation();
}

bool File::fileExists() {
	return(access(fullpath->c_str(), F_OK) == 0);
}

bool File::isDirectory() {
	// return (access(fullpath->c_str(), X_OK) == 0);
	struct stat info;
	if (!stat(fullpath->c_str(), &info)) {
		if (S_ISDIR(info.st_mode)) {
			return true;
		}
		return false;
	}
	return false;
}

bool File::nameHasSlash() {
	size_t lastChar = fullpath->length() - 1;
	return (fullpath->at(lastChar) == '/');
}

void	File::extractFileName() {
	std::string tmp;
	size_t questionMark = uri.find_last_of('?');
	size_t lastSlash = uri.find_last_of('/');

	tmp = questionMark != std::string::npos ? uri.substr(0, questionMark) : uri;
	if (lastSlash == tmp.length() - 1) {//slash mamorah walou oula morah question mark
		if (lastSlash == 0) {
			filename = "/";
			return;
		}
		size_t newDelim = lastSlash - 1;
		lastSlash = tmp.find_last_of('/', newDelim);
	}
	filename = tmp.substr(lastSlash + 1, tmp.length() - lastSlash);
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
        if (!access(path.c_str(), F_OK)) {
            (*fullpath) += *it;
			uri += *it;
			return true;
        }
    }
	return false;
}

bool	File::fileCgiSupport() {
	if (!existing || directory) { // need to ask if directory with cgi extention should be sent to cgi
		return false;
	}
	return (loc->cgi_bin.first == extention);
}

void	File::setFileInformation() {
	existing = fileExists();
	directory = isDirectory();
	endWithSlash = nameHasSlash();
	if (existing && directory && (!endWithSlash)) {
		uri += "/";
		*fullpath += "/";
	}
	if (directory) {
		indexFound = concatinateIndexFile();
	}
	extractFileName();
	extractExtention();
	cgi = fileCgiSupport();
	separatePathInfo();
}
