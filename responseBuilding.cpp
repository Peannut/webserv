std::string buildErrorResponse(const Request &request) {
	std::string headers;
	std::map<enum, std::string> statusCodes = {
		{0, " 400 Bad Request"},
		{1, " 405 Method Not Allowed"},
		{2, " 505 HTTP Version Not Supported"},
		{3, " 411 Length Required"}
	};

	headers += request._version;
	std::map<enum, std::string>::iterator it = errorCodes.find(request._error);
	if (it != errorCodes.end()) {
		headers += it->second;
	}
	else {
		headers += " 501 Not Implemented";
	}
	return headers;
}