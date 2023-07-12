#include "includes.hpp"

int main (int ac, char **av) {

	Request parsedreq;
	Response response;

	if (checkRequestError(parsedreq)) {
		ResponseHeaders = buildErrorResponse(parsedreq);
		return 1;
	}
	Response response = generateResponse(parsedreq);

	//serve the response;

	return 0;
}