/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoukaddo <zoukaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 15:03:03 by zwina             #+#    #+#             */
/*   Updated: 2023/07/14 10:35:40 by zoukaddo         ###   ########.fr       */
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
    Config & config = webserv._conf;
    struct addrinfo *records;
    SOCKET_FD fdsock_server;

    for (size_t sz = config.config.size(), i = 0; i < sz; ++i)
    {
        Server & server = config.get_server(i);

        records = our_getaddrinfo(server.get_host().data(), server.get_port().data());
        fdsock_server = our_bind(records);
        our_listen(fdsock_server);
        webserv.add_connection(LISTEN_ENABLE, fdsock_server, server);
        freeaddrinfo(records);
    }
}

void start_multiplexing(WebServ & webserv)
{
    while (1337 & 42)
    {
        our_poll(webserv._sockets);
        for (size_t i = 0; i < webserv._number_of_connections; ++i)
        {
            Connection & conn = webserv.get_connection(i);
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

int main(int ac, char **av, char **envp)
{
    UNUSED(envp);

    WebServ webserv;

	if (ac  != 2)
	{
        std::cerr << ANSI_BOLD << ANSI_RED << ANSI_ULINE;
		std::cerr << "Required one argument." << std::endl;
        std::cerr << ANSI_RESET;
		return (1);
	}
    try {
        webserv._conf.setupconfig(av[1]);
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
    catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
        return 1;
	}
    return 0;
}
