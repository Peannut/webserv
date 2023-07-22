#include "includes.hpp"

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
    return (access(path.c_str(), X_OK) == 0);
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
			return false;
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
