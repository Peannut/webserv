/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynuiga <ynuiga@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 11:05:22 by ynuiga            #+#    #+#             */
/*   Updated: 2023/07/11 11:05:58 by ynuiga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESPONSE_HPP
# define RESPONSE_HPP

struct Response {
    int statusCode;
    size_t contentLength;
    const Request *request;
    std::string statusMessage;
    std::string contentType;
    std::string content;
    std::fstream bodyFile;
    std::string _message;
    size_t _message_size;
    size_t _offset;

    Response(const Request *req) : request(req){}
    Response(int code, const std::string& message, const std::string& type, const std::string& body)
        : statusCode(code), statusMessage(message), contentType(type), content(body) {}
    void setStatusCode(const int &sc);
    void setStatusMessage(const std::string &sm);
    void setContentType(const std::string &ct);
    void setContentlength(const size_t &cl);
    void setResponsefields(const int &sc, const std::string &sm);
    void fillBodyFile( const Server &server );
    size_t getbodySize( void );
    std::string getContentType( void );
    void serving(const Server &server, const Location *loc, const std::string &loc_Path);
    size_t extract();
    void seek_back(const size_t & amount);
    bool is_done();
};  

#endif
