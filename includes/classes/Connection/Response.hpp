/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoukaddo <zoukaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 11:05:22 by ynuiga            #+#    #+#             */
/*   Updated: 2023/07/15 16:03:24 by zoukaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESPONSE_HPP
# define RESPONSE_HPP

struct Response {
    int statusCode;
    const Request *request;
    Cgi _cgi;
    std::string statusMessage;
    std::string contentType;
    std::string content;
    std::string Headers;

    Response(const Request *req) : request(req){}
    Response(int code, const std::string& message, const std::string& type, const std::string& body)
        : statusCode(code), statusMessage(message), contentType(type), content(body) {}
    void serving(const Server &server, const Location *loc, const std::string &loc_Path);
};

#endif
