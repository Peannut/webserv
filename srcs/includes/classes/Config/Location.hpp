#ifndef LOCATION_HPP
#define LOCATION_HPP

#include "prototypes.hpp"

struct Location
{
	std::string root; // root path
	bool autoindex; // on or off 
	std::vector<std::string> index; // index
	std::set<std::string> methods; // set of methods for get and post and delete only
	std::pair<short,std::string> redirect; // code and url
	std::string upload_pass; // upload pass path
	std::pair<std::string, std::string> cgi_bin; // extension and path

	Location();
};

#endif // LOCATION_HPP
