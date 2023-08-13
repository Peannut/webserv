#include "includes.hpp"

// This global variable will hold all the return of the system call functions that will fail if they return -1
int err;
// This is the buffer that will be passed to recv function to receive data from the client
char buffer[BUFFER_SIZE];

std::map<short, const char*> statusCodeMap;
void init_statusCodeMap()
{
    statusCodeMap[200] = "OK";
    statusCodeMap[201] = "Created";
    statusCodeMap[202] = "Accepted";
    statusCodeMap[203] = "Non-Authoritative Information";
    statusCodeMap[204] = "No Content";
    statusCodeMap[205] = "Reset Content";
    statusCodeMap[206] = "Partial Content";
    statusCodeMap[300] = "Multiple Choices";
    statusCodeMap[301] = "Moved Permanently";
    statusCodeMap[302] = "Found";
    statusCodeMap[303] = "See Other";
    statusCodeMap[304] = "Not Modified";
    statusCodeMap[307] = "Temporary Redirect";
    statusCodeMap[308] = "Permanent Redirect";
    statusCodeMap[400] = "Bad Request";
    statusCodeMap[401] = "Unauthorized";
    statusCodeMap[402] = "Payment Required";
    statusCodeMap[403] = "Forbidden";
    statusCodeMap[404] = "Not Found";
    statusCodeMap[405] = "Method Not Allowed";
    statusCodeMap[406] = "Not Acceptable";
    statusCodeMap[407] = "Proxy Authentication Required";
    statusCodeMap[408] = "Request Timeout";
    statusCodeMap[409] = "Conflict";
    statusCodeMap[410] = "Gone";
    statusCodeMap[411] = "Length Required";
    statusCodeMap[412] = "Precondition Failed";
    statusCodeMap[413] = "Request Too Large";
    statusCodeMap[414] = "Request-URI Too Long";
    statusCodeMap[415] = "Unsupported Media Type";
    statusCodeMap[416] = "Range Not Satisfiable";
    statusCodeMap[417] = "Expectation Failed";
    statusCodeMap[426] = "Upgrade Required";
    statusCodeMap[500] = "Internal Server Error";
    statusCodeMap[501] = "Not Implemented";
    statusCodeMap[502] = "Bad Gateway";
    statusCodeMap[503] = "Service Unavailable";
    statusCodeMap[504] = "Gateway Timeout";
    statusCodeMap[505] = "HTTP Version Not Supported";
}

void setup_webserv(WebServ & webserv)
{
    Config & config = webserv._conf;
    struct addrinfo *records;
    SOCKET_FD fdsock_server;

    for (std::map<std::pair<int, short>, std::vector<Server*> >::iterator it = config.configMap.begin(); it != config.configMap.end(); ++it)
    {
        std::vector<Server *> & servers = it->second;
        try
        {
            records = our_getaddrinfo(servers[0]->get_host().data(), servers[0]->get_port().data());
            fdsock_server = our_bind(records);
            our_listen(fdsock_server);
            webserv.add_connection(LISTEN_ENABLE, fdsock_server, servers);
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
                if ((*conn._res)._cgi.pid != -1 && !(*conn._res)._cgi._isDone)
                    (*conn._res).cgi_wait();
                else
                    sending(webserv, i);
            }
            else if (conn.is_error())
                webserv.remove_connection(i);
        }
    }
}

int main(int ac, char **av, char **envp)
{
    UNUSED(envp);

    init_statusCodeMap();
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
