#include "includes.hpp"

Response::Response(Request *req)
: request(req)
, _message_size()
, _offset()
, contentLength()
{}

void    Response::settingServerForCgi(const Server *server) {
    srv = server;
}

void Response::errorPageHtml() {
    std::string page = "<!DOCTYPE html>\n"
    "<html>\n"
    "<head>\n"
    "<title>ERROR</title>\n"
    "<style>\n"
    "body {background-color: black;text-align: center;}\n"
    "h1   {color: red;font-size: 3rem}\n"
    "p    {color: white;}\n"
    "</style>\n"
    "</head>\n"
    "<body>\n"
    "\n"
    "<h1>Error Occurred</h1>\n"
    "<p>There Was An Error While Trying To Solve Your Request</p>\n"
    "\n"
    "</body>\n"
    "</html>";
    std::ofstream outfile("/tmp/error.html");
    outfile << page;
    bodyFile.open("/tmp/error.html");
}

void    Response::buildingRedirectHeaders(const std::string &RedirectionLocation) {
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
    _message += "\r\nLocation: ";
    _message += RedirectionLocation;
	_message += "\r\n\r\n";
	_message_size = _message.length();
}

void    Response::handlingRedirection(const Server &server, const Location *loc) {
    UNUSED(server);
    std::stringstream tmp;
    if (loc->redirect.first >= 301 && loc->redirect.first <= 308) {
        setResponsefields(loc->redirect.first, statusCodeMap[loc->redirect.first]);
        buildingRedirectHeaders(loc->redirect.second);
    }
    else {
       setResponsefields(500, statusCodeMap[500]);
       errorPageHtml();
       getbodySize();
       buildResponseHeaders();
    }
}

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
    if (bodyFile.is_open() && amount && _offset >= _message_size) {
        bodyFile.seekg(amount, bodyFile.cur); // We have to update this line
    }
    _offset -= amount;
}

bool Response::is_done()
{
    return (_offset >= _message_size && (!bodyFile.is_open() || bodyFile.eof()));
}

void	Response::getFileStructure(File *file) {
	fileinfo = file;
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

std::string Response::generateRandomName() {
    time_t timestamp = std::time(NULL);
    std::string currentTime = ctime(&timestamp);
    return currentTime;
}

void	Response::serveErrorPage(const Server &srv, const short &errCode, const std::string &statMessage) {
	std::map<short, std::string>::const_iterator it = srv.error_pages.find(errCode);
    setResponsefields(errCode, statMessage);
    if(it == srv.error_pages.end()) {
        errorPageHtml();
        getbodySize();
        buildResponseHeaders();
        return;
    }
    bodyFile.open(it->second.data());
    getbodySize();
    buildResponseHeaders();
}

void Response::fillBodyFile( const Server &server ) { //khas server maydouzch liya const
    bodyFile.open(request->_path.data());

    if (!bodyFile.is_open()) {
        if (errno == EACCES) {
            setResponsefields(403, statusCodeMap[403]);
            std::map<short, std::string>::const_iterator it = server.error_pages.find(403);
            if(it == server.error_pages.end()) {
                    errorPageHtml();
                return;
            }
            bodyFile.open(it->second.data());
        }
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
	_message += "\r\nConnection: Close\r\nContent-length: ";
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
    if (access(request->_path.c_str(), W_OK)) {
        serveErrorPage(server, 403, statusCodeMap[403]);
        return ;
    }
    if (std::remove(request->_path.c_str())) {
        serveErrorPage(server, 500, statusCodeMap[500]);
        return ;
    }
    serveErrorPage(server, 204, statusCodeMap[204]);
}

void    Response::deleteAllDirContent(std::string path, const Server &server) {
    DIR* dir = opendir(path.c_str());
    if (dir) {
        struct dirent* entry;
        while ((entry = readdir(dir)) != NULL) {
            std::string name = entry->d_name;
            if (name != "." && name != "..") {
                std::string fullPath = path + name;
                struct stat pathinfo;
                if (stat(fullPath.c_str(), &pathinfo)) {
                    setResponsefields(500, statusCodeMap[500]);
                }
                else {
                    if (S_ISDIR(pathinfo.st_mode)) {
                        fullPath.push_back('/');
                        deleteAllDirContent(fullPath, server);
                    } else if (S_ISREG(pathinfo.st_mode)) {
                        if (access(fullPath.c_str(), W_OK) == 0) {
                            if (std::remove(fullPath.c_str())) {
                                setResponsefields(500, statusCodeMap[500]);
                            }
                            else {
                                setResponsefields(204, statusCodeMap[204]);
                            }
                        } else {
                        setResponsefields(403, statusCodeMap[403]);
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

void    Response::uploadContent(const Server &server, const Location *loc) {
    UNUSED(server);
    std::ofstream outfile((loc->upload_pass + "/" + fileName).c_str());
    outfile << request->_body;
    outfile.close();
    setResponsefields(201, statusCodeMap[201]);
    buildResponseHeaders();
}

void    Response::setPathInformation(const Location *loc) {
    size_t cgiExtentionIndex = this->request->_path.find(loc->cgi_bin.first, 0) + loc->cgi_bin.first.length();
    pathinformation = this->request->_path.substr(cgiExtentionIndex, this->request->_path.length() - cgiExtentionIndex);
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
                page += "<li><a href=\"" + fileinfo->uri + name + "\">" + name + "</a></li>\n";
            }
        }
        closedir(dir);
    }
    page += "</ul>\n";
    page += "</body></html>\n";
    std::ofstream outfile("/tmp/indexpage.html");
    outfile << page;
    bodyFile.open("/tmp/indexpage.html");
}

void Response::serving(const Server & server, const Location * loc) {
    if (request->_error || loc->redirect.first) {
        if (request->_error) {
            serveErrorPage(server, this->request->_error, statusCodeMap[this->request->_error]);
        }
        else {
            handlingRedirection(server, loc);
        }
    }
    else {
        File file(&(this->request->_path), this->request->_uri, loc);
        getFileStructure(&file);
        if (file.cgi) {
            settingServerForCgi(&server);
            if (!handleCGI(file))
                cgi_supervisor(file);
        }
        else {
            if (this->request->_method == GET_method) { 
                servingFileGet(this, server, loc, file);
            }
            else if (this->request->_method == POST_method) {
                postFile(this, server, loc, file);
            }
            else if (this->request->_method == DELETE_method) {
                deletingFile(this, server, loc, file);
            }
        }
    }
}
