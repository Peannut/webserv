#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include "prototypes.hpp"

struct Response
{
    Request *request;
    Cgi     _cgi;
    int statusCode;
    std::string statusMessage;
    std::string contentType;
    std::string content;
    std::fstream bodyFile;
    std::string _message;
    std::string fileName;
    std::string pathinformation;
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
    bool hasIndexFile(const Location *loc);
    void    removeFile(const Server &server);
    size_t extract();
    void seek_back(const size_t & amount);
    bool is_done();
    void serving(const Server &server, const Location *loc, const std::string &loc_Path);


    //peanut functions
    void env_maker(File &file);
    int handleCGI(File &file);
    void cgiResponse(void);
    void cgi_execve(const Location &loc, File &file);
    void data_reader(void);
    void reqbodysend(void);
    void cgi_wait(void);
    std::string env_grabber(const std::string& key);
    void cgi_supervisor(File &file);
    // -----------------
    void    nameUploadFile();
    void    setFileName( const std::string & );
    std::string generateRandomName();
    void    uploadContent(const Server  &server);
    void    setPathInformation(const Location *);
    void    generateIndexPage();
    void    deleteAllDirContent(std::string path, const Server &server);
    void    buildResponseHeaders( void );
};

#endif // RESPONSE_HPP
