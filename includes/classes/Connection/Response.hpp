/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoukaddo <zoukaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 11:05:22 by ynuiga            #+#    #+#             */
/*   Updated: 2023/08/01 15:04:31 by zoukaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
    bool hasAutoIndex(const Location *loc);
    void    removeFile(const Server &server);
    size_t extract();
    void seek_back(const size_t & amount);
    bool is_done();
    void serving(const Server &server, const Location *loc, const std::string &loc_Path);


    //peanut functions
    void env_maker(void);
    int handleCGI(void);
    void cgiResponse(void);
    void cgi_execve(const Location &loc);
    void data_reader(void);
    void reqbodysend(void);
    std::string env_grabber(const std::string& key);
    // -----------------
    void    nameUploadFile();
    void    setFileName( const std::string & );
    std::string generateRandomName();
    void    uploadContent();
    void    setPathInformation(const Location *);
};

#endif // RESPONSE_HPP
