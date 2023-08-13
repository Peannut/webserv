/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoukaddo <zoukaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 11:05:22 by ynuiga            #+#    #+#             */
/*   Updated: 2023/08/11 11:20:56 by zoukaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include "prototypes.hpp"
struct Response
{
    Request *request;
    const Server  *srv;
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
    File *fileinfo;

    Response(Request *req);

    void setStatusCode(const int &sc);
    void setStatusMessage(const std::string &sm);
    void setContentType(const std::string &ct);
    void setContentlength(const size_t &cl);
    void setResponsefields(const int &sc, const std::string &sm);
    void fillBodyFile( const Server &server );
    void    serveErrorPage(const Server &srv, const short &errCode, const std::string &statMessage);
    // void    serveDefaultErrorPage(const short &, const std::string &);
    void getbodySize( void );
    std::string getContentType( void );
    bool hasIndexFile(const Location *loc);
    void    removeFile(const Server &server);
    size_t extract();
    void seek_back(const size_t & amount);
    bool is_done();
    void serving(const Server &server, const Location *location);


    //peanut functions
    int env_maker(File &file);
    int handleCGI(File &file);
    void cgiResponse(void);
    void cgi_execve(File &file);
    void data_reader(void);
    void reqbodysend(void);
    void cgi_wait(void);
    std::string env_grabber(const std::string& key);
    void cgi_supervisor(File &file);
    // -----------------
    void    nameUploadFile();
    void    setFileName( const std::string & );
    std::string generateRandomName();
    void    uploadContent(const Server  &server, const Location *loc);
    void    setPathInformation(const Location *);
    void    generateIndexPage();
    void    deleteAllDirContent(std::string path, const Server &server);
    void    buildResponseHeaders( void );
    void    getFileStructure(File *file);
    void    settingServerForCgi(const Server *server);
    void    handlingRedirection(const Server &server, const Location *loc);
    void    buildingRedirectHeaders(const std::string &RedirectionLocation);
    void    errorPageHtml();
};

#endif // RESPONSE_HPP
