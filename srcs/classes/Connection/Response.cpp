/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynuiga <ynuiga@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 15:03:17 by zwina             #+#    #+#             */
/*   Updated: 2023/07/11 11:11:36 by ynuiga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.hpp"

void Response::serving(const Server &server, const Location *loc, const std::string &loc_Path) {
        Request req;
        Response response(&req);

        if (checkRequestError(response)) { //if request has an error;
                response.Headers = buildErrorResponseH(response);
                response.content = findErrorPage(response, server);
                //after building now the Response header and body should start sending chunk by chunk to multiplexing;
        }
        //if request has no errors
        else if (response.request->_method == GET_method) { //first thing check if resourse is found in root if no error404 we pretend now it always exists
                servingFileGet(&response ,server, loc, loc_Path);
        // if (isDirectory(response.request->_path)) { // a directory is requested
        //         if (hasSlashEnd(request._path)) { //dir has '/' at the end
        //                 //check if directory has indexfile (search for "index.html" in the dir) | if found serve it
        //                 //if directory has no indexfile | check if autoindex is on
        //                         // if on return autoindex of directory
        //                         // else (autoindex off) return 403 Forbidden;
        //         }
        //         else { //dir does not have '/' at the end
        //                 response.statusCode = 301;
        //                 response.statusMessage = "Moved Pemanently";
        //         }
        // }
        // else { // a file is requested
        //         if (resourceExists(request._path)) {
        //                 response.statusCode = 200;
        //                 response.statusMessage = "OK";
        //                 response.contentType = getContentType(request._path);
        //                 response.content = readResource(request._path);
        //                 }
        //         else {
        //                 response.statusCode = 404;
        //                 response.statusMessage = "Not Found";
        //                 }
        //         }
        }
        response.Headers = getResponseHeaders(response, server, loc, loc_Path);
}
