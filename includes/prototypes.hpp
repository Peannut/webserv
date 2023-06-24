/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototypes.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwina <zwina@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 17:44:37 by zwina             #+#    #+#             */
/*   Updated: 2023/06/24 15:08:11 by zwina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTOTYPES_HPP
#define PROTOTYPES_HPP

// Defines
#define UNUSED(x) (void)(x) // unused variable
#define SOCKET struct pollfd
#define SOCKET_FD int
#define LISTEN_ENABLE true // the type of connection, is it a server socket (aka. listen) or a client socket
#define POLL_TIME 100 // the time that poll() waits in milliseconds
#define BACK_LOG 10 // one socket can handle BACK_LOG number of connection
#define BUFFER_SIZE (size_t)512 // the size of the receiving the sending buffer

#define ANSI_RESET        "\033[0m"
#define ANSI_BOLD         "\033[1m"
#define ANSI_ULINE        "\033[4m"
#define ANSI_ITALIC       "\033[3m"
#define ANSI_RED          "\033[31m"

// This is the declaration, the definition is in the main.cpp file
extern int err;
extern char buffer[BUFFER_SIZE];
extern const std::string response;

// The declarations of the structs
struct WebServ;
struct Config;
struct Server;
struct Location;
struct Connection;
struct Request;
struct Response;

// The declarations of the functions
struct addrinfo *   our_getaddrinfo     (const char *hostname, const char *servname);
SOCKET_FD           our_bind            (struct addrinfo *records);
SOCKET_FD           our_socket          (const int &domain, const int &type, const int &protocol);
void                our_listen          (const SOCKET_FD &fdsock);
void                setup_webserv       (WebServ & webserv);
void                start_multiplexing  (WebServ & webserv);
void                our_poll            (std::vector<SOCKET> & sockets);
void                accepting           (WebServ & webserv, const size_t & index);
void                receiving           (WebServ & webserv, const size_t & index);
void                sending             (WebServ & webserv, const size_t & index);

#endif // PROTOTYPES_HPP
