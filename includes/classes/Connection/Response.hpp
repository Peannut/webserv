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
    std::string statusMessage;
    std::string contentType;
    std::string content;
    std::string Headers;

    Response() {}
    Response(int code, const std::string& message, const std::string& type, const std::string& body)
        : statusCode(code), statusMessage(message), contentType(type), content(body) {}
};

#endif