#include "includes.hpp"

int main (int ac, char **av) {

	Request parsedreq;
	// std::cout << getContentType(parsedreq._path)<< std::endl;
	// std::cout << readResource("Makefile") << std::endl;
	Response response = generateResponse(parsedreq);

	//serve the response;

	return 0;
}