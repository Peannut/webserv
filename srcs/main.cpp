/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoukaddo <zoukaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 15:03:03 by zwina             #+#    #+#             */
/*   Updated: 2023/08/08 19:47:36 by zoukaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.hpp"

// This global variable will hold all the return of the system call functions that will fail if they return -1
int err;
// This is the buffer that will be passed to recv function to receive data from the client
char buffer[BUFFER_SIZE];

void setup_webserv(WebServ & webserv)
{
    Config & config = webserv._conf;
    struct addrinfo *records;
    SOCKET_FD fdsock_server;

    for (size_t sz = config.config.size(), i = 0; i < sz; ++i)
    {
        Server & server = config.get_server(i);
        try
        {
            records = our_getaddrinfo(server.get_host().data(), server.get_port().data());
            fdsock_server = our_bind(records);
            our_listen(fdsock_server);
            webserv.add_connection(LISTEN_ENABLE, fdsock_server, server);
            freeaddrinfo(records);
        }
        catch (const int & n) {
            // getaddrinfo errors
            std::cerr << ANSI_BOLD << ANSI_RED << ANSI_ULINE;
            std::cerr << "getaddrinfo() => [" << n << "] " << gai_strerror(n) << std::endl;
            std::cerr << ANSI_RESET;
        }
        catch (const char * s) {
            // errno errors
            std::cerr << ANSI_BOLD << ANSI_RED << ANSI_ULINE;
            std::cerr << s << "() => [" << errno << "] " << strerror(errno) << std::endl;
            std::cerr << ANSI_RESET;
        }
    }
    if (webserv._number_of_connections == 0) throw ("Zero Server !");
}

void start_multiplexing(WebServ & webserv)
{
    std::vector<SOCKET_POLL> & sockets = webserv._sockets;
    while (1337 & 42)
    {
        ///////////////////////POLLING///////////////////////
        err = poll(sockets.data(), sockets.size(), POLL_TIME);
        if (err == -1) continue;
        /////////////////////////////////////////////////////
        for (size_t i = 0; i < webserv._number_of_connections; ++i)
        {
            Connection & conn = webserv.get_connection(i);
            if (conn.can_read())
            {
                if (conn._isListen)
                    accepting(webserv, i);
                else if (conn.get_passed_time() > TIMEOUT)
                    webserv.remove_connection(i);
                else
                    receiving(webserv, i);
            }
            else if (conn.can_write())
            {
                if (conn.get_res()._cgi.pid != -1 && !conn.get_res()._cgi._isDone)
                    conn.get_res().cgi_wait();
                else
                    sending(webserv, i);
            }
            else if (conn.is_error() || (!conn._isListen && conn.get_passed_time() > TIMEOUT))
                webserv.remove_connection(i);
        }
    }
}

int main(int ac, char **av, char **envp)
{
    UNUSED(envp);

    WebServ webserv;

    try {
        if (ac != 2) throw ("Required one argument !");
        webserv._conf.setupconfig(av[1]);
        setup_webserv(webserv);
    }
    catch (const char * s) {
        // errno errors
        std::cerr << ANSI_BOLD << ANSI_RED << ANSI_ULINE;
        std::cerr << s << std::endl;
        std::cerr << ANSI_RESET;
        return 1;
    }
    catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
        return 1;
	}

    start_multiplexing(webserv);

    return 0;
}
