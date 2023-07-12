#include "includes.hpp"

int main (int ac, char **av) {

	Response response;

	if (checkRequestError(parsedreq)) {
		response.Headers = buildErrorResponseH(parsedreq);
		response.content = buildErrorResponseB(parsedreq);
		return 1;
	}
	response = generateResponse(parsedreq);
	//nbuildi response l3adya ila makan 7ta error;
	// Response response = generateResponse(parsedreq);

	//serve the response;

	return 0;
}