/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototypes.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoukaddo <zoukaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 15:19:56 by zoukaddo          #+#    #+#             */
/*   Updated: 2023/08/09 09:49:27 by zoukaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef PROTOTYPES_HPP
#define PROTOTYPES_HPP

// Defines
#define UNUSED(x) (void)(x) // unused variable
#define SOCKET_POLL struct pollfd
#define SOCKET_FD int
#define LISTEN_ENABLE true // the type of connection, is it a server socket (aka. listen) or a client socket
#define TIMEOUT (time_t)60 // the maximum number of second that we will wait if the client socket freezed
#define POLL_TIME 0 // the time that poll() waits in milliseconds
#define BACK_LOG 10 // one socket can handle BACK_LOG number of connection
#define BUFFER_SIZE (size_t)8192 // the size of the receiving the sending buffer
#define URI_LIMIT 8192 // the maximum size of the uri in the request

#define ANSI_RESET      "\033[0m"
#define ANSI_BOLD       "\033[1m"
#define ANSI_ULINE      "\033[4m"
#define ANSI_ITALIC     "\033[3m"
#define ANSI_RED        "\033[31m"
#define ANSI_GREEN      "\033[32m"
#define ANSI_YELLOW	    "\033[33m"

// This is the declaration, the definition is in the main.cpp file
extern int err;
extern char buffer[BUFFER_SIZE];

// The declarations of the structs
struct WebServ;
struct Config;
struct Server;
struct Location;
struct Connection;
struct Request;
struct Response;
struct File;
struct Cgi;

// The declarations of the functions

// <-- main.cpp -->
void setup_webserv(WebServ & webserv);
void start_multiplexing(WebServ & webserv);
// <-- multiplexing.cpp -->
struct addrinfo *   our_getaddrinfo     (const char *hostname, const char *servname);
SOCKET_FD           our_bind            (struct addrinfo *records);
SOCKET_FD           our_socket          (const int &domain, const int &type, const int &protocol);
void                our_listen          (const SOCKET_FD &fdsock);
void                setup_webserv       (WebServ & webserv);
void                start_multiplexing  (WebServ & webserv);
void                accepting           (WebServ & webserv, const size_t & index);
void                receiving           (WebServ & webserv, const size_t & index);
void                sending             (WebServ & webserv, const size_t & index);
void                serving             (WebServ & webserv, const size_t & index);
// <-- Config/utils.cpp -->
int line_empty(const std::string& line);
ssize_t stringToLong(const std::string& str);
std::vector<std::string> split(const std::string& str, char lim);
std::string convertToIPAddress(size_t ip);
std::string convertPortToString(short port);
// <-- Request/utils.cpp -->
bool isUnreserved(const char & c);
bool isReserved(const char & c);
bool isOWS(const char & c);
bool isHEXDIG(const char & c);
bool isVchar(const char & c);
bool isTchar(const char & c);
bool isMethodChar(const char & c);
bool isPathChar(const char & c);
bool isQueryChar(const char & c);
void toupperFieldKey(std::string & field_key);
void trimFieldVal(std::string & field_val);
bool isContentLengthValValid(const std::string & val);
bool isTransferEncodingValValid(const std::string & val);
size_t matching_location(const std::string & path, const std::string & location_path);
// </--Response/utils.cpp-->
std::string readResource(const std::string &path);
std::string findErrorPage(const Response &response,const Server &srv);
bool        isDirectory(const std::string &path);
bool        hasSlashEnd(const std::string &path);
bool        resourceExists (const std::string &path);
bool        fileCgi(std::string fullpath, const Location *loc);
bool        outilsHasIndex(std::string *path, const Location    *loc);
bool        pathSupportUpload(Response *response, const Location *loc);
void        buildErrorResponse(const Server &server, Response *response);
void        deletingFile(Response *res, const Server &server, const Location *loc, const File &file);
void        postFile(Response	*response, const Server	&server, const Location	*loc, const File &file);
void        servingFileGet(Response *response ,const Server &server, const Location *loc, const File &file);
// void    buildResponseHeaders(Response &response);
// std::string getResponseHeaders(const Response &response, const Server &srv, const Location *loc, const std::string &loc_Path);


/*
    Thing To Do At The End :
      X 1- remove the response global variable.
        2- remove the all the :.
      X 3- remove the checking of errno after send and recv.
        4- remove the member variable _message in the Request.
        5- check the allowed functions.
*/
#endif // PROTOTYPES_HPP
