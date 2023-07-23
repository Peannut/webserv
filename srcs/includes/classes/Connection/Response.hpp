#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include "prototypes.hpp"

struct Response
{
    Request *request;
    int statusCode;
    std::string statusMessage;
    std::string contentType;
    std::string content;
    std::fstream bodyFile;
    std::string _message;
    size_t _message_size;
    size_t _offset;
    size_t contentLength;

    Response(Request *req);

    void setStatusCode(const int &sc);
    void setStatusMessage(const std::string &sm);
    void setContentType(const std::string &ct);
    void setContentlength(const size_t &cl);
    void setResponsefields(const int &sc, const std::string &sm);
    void fillBodyFile( const Server &server );
    void    serveErrorPage(const Server &srv, const short &errCode, const std::string &statMessage);
    void    serveDefaultErrorPage( void );
    void getbodySize( void );
    std::string getContentType( void );
    bool hasAutoIndex(const Location *loc);
    void    removeFile(const Server &server);
    size_t extract();
    void seek_back(const size_t & amount);
    bool is_done();
    void serving(const Server &server, const Location *loc, const std::string &loc_Path);
};

#endif // RESPONSE_HPP