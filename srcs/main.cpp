/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwina <zwina@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 15:03:03 by zwina             #+#    #+#             */
/*   Updated: 2023/07/10 10:31:15 by zwina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.hpp"

// This global variable will hold all the return of the system call functions that will fail if they return -1
int err;
// This is the buffer that will be passed to recv function to receive data from the client
char buffer[BUFFER_SIZE];
// This is just a response string test
const std::string response
(
    "HTTP/1.1 200 OK\r\n"
    "Content-length: 14\r\n"
    "Content-Type: text/html\r\n"
    "Connection: close\r\n\r\n"
    "<h1>hello</h1>"
);

void setup_webserv(WebServ & webserv)
{
    struct addrinfo *records;
    SOCKET_FD fdsock_server;

    // for (size_t sz = webserv._conf._srvs.size(), i = 0; i < sz; ++i) {
    for (size_t sz = 1, i = 0; i < sz; ++i)
    {
        records = our_getaddrinfo("127.0.0.1", "8080");
        fdsock_server = our_bind(records);
        our_listen(fdsock_server);
        webserv.add_connection(LISTEN_ENABLE, fdsock_server);
        freeaddrinfo(records);
    }
}

void start_multiplexing(WebServ & webserv)
{
    while (1337 & 42)
    {
        our_poll(webserv._sockets);
        for (size_t sz = webserv._number_of_connections, i = 0; i < sz; ++i)
        {
            Connection & conn = webserv.get_connection(i);
            // std::cout << "fd["<<i<<"]" << conn._socket->fd << std::endl;
            if (conn.can_read())
            {
                if (conn._isListen)
                    accepting(webserv, i);
                else
                    receiving(webserv, i);
            }
            else if (conn.can_write())
                sending(webserv, i);
            else if (conn.is_error())
                webserv.remove_connection(i);
            else if (!conn._isListen && conn._isMustServeNow)
                serving(webserv, i);
        }
    }
}

int main(int argc, char **argv, char **envp)
{
    UNUSED(argc);
    UNUSED(argv);
    UNUSED(envp);

    WebServ webserv;

    try {
        // read_configfile(webserv);
        setup_webserv(webserv);
        start_multiplexing(webserv);
    }
    catch (const int & n) {
        // getaddrinfo errors
        std::cerr << ANSI_BOLD << ANSI_RED << ANSI_ULINE;
        std::cerr << "getaddrinfo() => [" << n << "] " << gai_strerror(n) << std::endl;
        std::cerr << ANSI_RESET;
        return 1;
    }
    catch (const char * s) {
        // errno errors
        std::cerr << ANSI_BOLD << ANSI_RED << ANSI_ULINE;
        std::cerr << s << "() => [" << errno << "] " << strerror(errno) << std::endl;
        std::cerr << ANSI_RESET;
        return 1;
    }
    return 0;
}
