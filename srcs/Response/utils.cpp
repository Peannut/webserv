#include "includes.hpp"

bool checkRequestError(const Response &response) {
	return response.request->_error;
}

bool isDirectory(const std::string &path) {
	return (access(path.c_str(), X_OK) == 0);
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
		std::string dot = ".";
		std::string conType;
		size_t index = 0;
		while ((index = fullpath.find(dot, index)) != std::string::npos) {
			std::cout << "DKHELT L WHILE!" << std::endl;
			size_t closestSlash = fullpath.find_first_of('/', index);
			if (closestSlash == std::string::npos) {
				conType = fullpath.substr(index, fullpath.length() - index);
				std::cout << "file Extention = " << conType << "-------" << "cgi Extention = " << loc->cgi_bin.first << std::endl;
				return conType == loc->cgi_bin.first;
			}
			else {
				conType = fullpath.substr(index, closestSlash - index);
				if (conType == loc->cgi_bin.first) {
					std::cout << "l9it l file with cgi lwest!" << std::endl;
					return true;
				}
				index = closestSlash + 1;
			}
			std::cout << "file Extention = " << conType << "-------" << "cgi Extention = " << loc->cgi_bin.first << std::endl;
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
