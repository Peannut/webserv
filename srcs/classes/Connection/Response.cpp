#include "includes.hpp"

Response::Response(Request *req)
: request(req)
, _message_size()
, _offset()
{}

size_t Response::extract()
{
    size_t length = 0;
    while (length < BUFFER_SIZE)
    {
        if (_offset < _message_size)
            buffer[length++] = _message[_offset++];
        else if (bodyFile.is_open() && !bodyFile.eof())
        {
            char c = bodyFile.get();
            if (!bodyFile.eof()) {
                buffer[length++] = c;
                ++_offset;
            }
        }
        else break;
    }
    return (length);
}

void Response::seek_back(const size_t & amount)
{
    if (bodyFile.is_open() && amount && _offset >= _message_size)
        bodyFile.seekg(amount, bodyFile.cur); // We have to update this line
    _offset -= amount;
}

bool Response::is_done()
{
    return (_offset >= _message_size && (!bodyFile.is_open() || bodyFile.eof()));
}

std::string Response::getContentType( void ) {
	std::string conType;

	size_t lastSlash = request->_path.find_last_of('.');
	conType = request->_path.substr(lastSlash+ 1, request->_path.length() - lastSlash);

    if (conType == "css") {
		return "text/css";
	}
	else if (conType == "csv") {
		return "text/csv";
	}
	else if (conType == "gif") {
		return "image/gif";
	}
	else if (conType == "ico") {
		return "image/x-icon";
	}
	else if (conType == "jpeg" || conType == "jpg") {
		return "image/jpeg";
	}
	else if (conType == "js") {
		return "application/javascript";
	}
	else if (conType == "json") {
		return "application/json";
	}
	else if (conType == "png") {
		return "image/png";
	}
	else if (conType == "pdf") {
		return "application/pdf";
	}
	else if (conType == "svg") {
		return "image/svg+xml";
	}
	else if (conType == "txt") {
		return "text/plain";
	}
    return "text/html";
}

void Response::setStatusCode(const int &sc) {
    statusCode = sc;
}

void Response::setStatusMessage(const std::string &sm) {
    statusMessage = sm;
}

void Response::setContentType(const std::string &ct) {
    contentType = ct;
}

void Response::setContentlength(const size_t &cl) {
    contentLength = cl;
}

void    Response::setFileName( const std::string &newName) {
    fileName = newName;
}

void Response::setResponsefields(const int &sc, const std::string &sm) {
    std::string ct;

    ct = getContentType();
    setStatusCode(sc);
    setStatusMessage(sm);
    setContentType(ct);
}

void    Response::serveDefaultErrorPage() {
    bodyFile.open("srcs/Response/DefaultError/index.html");
    setResponsefields(500, "Internal Server Error");
}

std::string Response::generateRandomName() {
    time_t timestamp = std::time(NULL);
    std::string currentTime = ctime(&timestamp);
    return currentTime;
}

void	Response::serveErrorPage(const Server &srv, const short &errCode, const std::string &statMessage) {
	std::map<short, std::string>::const_iterator it = srv.error_pages.find(errCode);
        if(it == srv.error_pages.end()) {
            serveDefaultErrorPage();
            return;
        }
        bodyFile.open(it->second.data());
        setResponsefields(errCode, statMessage);
}

void Response::fillBodyFile( const Server &server ) { //khas server maydouzch liya const
    bodyFile.open(request->_path.data());

    if (!bodyFile.is_open()) {
        std::map<short, std::string>::const_iterator it = server.error_pages.find(500);
        if(it == server.error_pages.end()) {
            serveDefaultErrorPage();
            return;
        }
        bodyFile.open(it->second.data());
        setResponsefields(500, "Internal Server Error");
    }
    setResponsefields(200, "OK");
}

void Response::getbodySize( void ) {
    bodyFile.seekg(0, bodyFile.end);
    std::streampos filesize = bodyFile.tellg();
    bodyFile.seekg(0);
    contentLength = static_cast<size_t>(filesize);
}

bool Response::hasAutoIndex( const Location *loc) {
    for (std::vector<std::string>::const_iterator it = loc->index.begin(); it != loc->index.end(); ++it) {
        std::string fullpath = request->_path + *it;
        std::ifstream indexFile(fullpath.data());
        if (resourceExists(fullpath)) {
            request->_path += *it;
            return true;
        }
    }
    return false;
}

void Response::removeFile(const Server &server) {
    if (std::remove(request->_path.c_str())){
        serveDefaultErrorPage();
        return ;
    }
    serveErrorPage(server, 203, "No Content");
}

void    Response::nameUploadFile() {
    std::map<std::string, std::string>::iterator it = request->_fields.find("CONTENT_DISPOSITION");
    if (it != request->_fields.end()) {
        fileName = it->second;
        return;
    }
    fileName = generateRandomName();
}

void    Response::uploadContent() {
    std::ofstream fileName;
    fileName << request->_body;
    fileName.close();
}

void Response::serving(const Server &server, const Location *loc, const std::string &loc_Path) {

    if (request->_error) {
        buildErrorResponse(server, this);
    }
    else { //if request has no errors
        if (fileCgi(this->request->_path, loc)) {
            //////////////cgi//////////////
        }
        else if (this->request->_method == GET_method) { //first thing check if resourse is found in root if no error404 we pretend now it always exists
            servingFileGet(this ,server, loc, loc_Path);
        }
        else if (this->request->_method == POST_method) {
            postFile(this, server, loc);
        }
        else if (this->request->_method == DELETE_method) {
            deletingFile(this, server, loc);
        }
        // else{}
    }
    std::cout << "RESPONSE = [" << _message << ']' << std::endl;
}
