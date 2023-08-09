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
    buildResponseHeaders();
    //kansetti ou makanktebch f message + khasni nbda npasi l file object bach nbda nkhdem bih blast getContent type ect;

}

std::string Response::generateRandomName() {
    time_t timestamp = std::time(NULL);
    std::string currentTime = ctime(&timestamp);
    return currentTime;
}

void	Response::serveErrorPage(const Server &srv, const short &errCode, const std::string &statMessage) {
	std::map<short, std::string>::const_iterator it = srv.error_pages.find(errCode);
        if(it == srv.error_pages.end()) {
            std::cout << "mal9ach l error page li bgha!" << std::endl;
            serveDefaultErrorPage();
            return;
        }
        bodyFile.open(it->second.data());
        setResponsefields(errCode, statMessage);
        buildResponseHeaders();
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

void    Response::buildResponseHeaders() {
	std::stringstream tmp;
	_message += "HTTP/1.1 ";
	tmp << statusCode;
	_message += tmp.str();
	_message += " ";
	_message += statusMessage;
	_message += "\r\nContent-Type: ";
	_message += contentType;
	_message += "\r\nConnection: Close\r\nContent-lenght: ";
	tmp.str("");
	tmp << contentLength;
	_message += tmp.str();
	_message += "\r\n\r\n";
	_message_size = _message.length();
}

bool Response::hasIndexFile( const Location *loc) {
    for (std::vector<std::string>::const_iterator it = loc->index.begin(); it != loc->index.end(); ++it) {
        std::string fullpath = request->_path + '/' +  *it;
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

void    Response::deleteAllDirContent(std::string path, const Server &server) {
    DIR* dir = opendir(path.c_str());
    if (dir) {
        struct dirent* entry;
        while ((entry = readdir(dir)) != NULL) {
            std::string name = entry->d_name;
            if (name != "." && name != "..") {
                std::string fullPath = path + "/" + name;
                struct stat pathinfo;
                if (stat(fullPath.c_str(), &pathinfo)) {
                    serveDefaultErrorPage();
                }
                else {
                    if (isDirectory(fullPath)) {
                        deleteAllDirContent(fullPath, server);
                        rmdir(fullPath.c_str());
                    } else if (S_ISREG(pathinfo.st_mode)) {
                        if (access(fullPath.c_str(), W_OK) == 0) {
                            remove(fullPath.c_str());
                            serveErrorPage(server, 204, "No Content");
                        } else {
                        serveErrorPage(server, 403, "Forbidden");
                        }
                    }
                }
            }
        }
        closedir(dir);
    }
}

void    Response::nameUploadFile() {
    std::map<std::string, std::string>::iterator it = request->_fields.find("CONTENT_DISPOSITION");
    if (it != request->_fields.end()) {
        fileName = it->second;
        return;
    }
    fileName = generateRandomName();
}

void    Response::uploadContent(const Server &server) {
    std::ofstream fileName;

    serveErrorPage(server, 201, "Created");
    fileName << request->_body;
}

void    Response::setPathInformation(const Location *loc) {
    size_t cgiExtentionIndex = this->request->_path.find(loc->cgi_bin.first, 0) + loc->cgi_bin.first.length();
    pathinformation = this->request->_path.substr(cgiExtentionIndex, this->request->_path.length() - cgiExtentionIndex);
    std::cout << pathinformation << std::endl;
}

void    Response::generateIndexPage() {
    std::string page = "<html><head><title>Index of " + request->_path + "</title></head><body>\n";
    page += "<h1>Index of " + request->_path + "</h1>\n";
    page += "<ul>\n";

    DIR* dir = opendir(request->_path.c_str());
    if (dir) {
        struct dirent* entry;
        while ((entry = readdir(dir)) != NULL) {
            std::string name = entry->d_name;
            if (name != "." && name != "..") {
                page += "<li><a href=\"" + name + "\">" + name + "</a></li>\n";
            }
        }
        closedir(dir);
    }
    page += "</ul>\n";
    page += "</body></html>\n";
    _message += page;
}

void Response::serving(const Server &server, const Location *loc, const std::string &loc_Path) {

    UNUSED(loc_Path);
    if (request->_error) {
        buildErrorResponse(server, this);
    }
    else { //if request has no errors
        std::cout << "dkhel l else" << std::endl;
        File file(&(this->request->_path), this->request->_uri, loc);
        if (file.cgi) {
            std::cout << "dkhel l cgi" << std::endl;
            //////////////cgi//////////////
        }
        else {
            std::cout << "mal9ahch cgi" << std::endl;
            if (this->request->_method == GET_method) { 
                servingFileGet(this ,server, loc, file);
            }
            else if (this->request->_method == POST_method) {
                postFile(this, server, loc, file);
            }
            else if (this->request->_method == DELETE_method) {
                deletingFile(this, server, loc, file);
            }
        }
        // else{}
    }
    std::cout << "RESPONSE = [" << _message << ']' << std::endl;
}
