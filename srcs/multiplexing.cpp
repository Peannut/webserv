#include "includes.hpp"

struct addrinfo *our_getaddrinfo(const char *hostname, const char *servname)
{
    addrinfo *records;
    addrinfo hints;

    bzero(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    err = getaddrinfo(hostname, servname, &hints, &records);
    if (err) throw (err);

    return records;
}

SOCKET_FD our_bind(struct addrinfo *records)
{
    struct addrinfo *tmp = records;
    SOCKET_FD fdsock;

    do {
        fdsock = our_socket(tmp->ai_family, tmp->ai_socktype, tmp->ai_protocol);

        err = bind(fdsock, tmp->ai_addr, tmp->ai_addrlen);
        if (err != -1) break;
        close(fdsock);
        tmp = tmp->ai_next;
    } while (tmp);
    if (err == -1) throw ("bind");

    return fdsock;
}

SOCKET_FD our_socket(const int & domain, const int & type, const int & protocol)
{
    SOCKET_FD fdsock = socket(domain, type, protocol);
    if (fdsock == -1) throw ("socket");

    err = fcntl(fdsock, F_SETFL, O_NONBLOCK);
    if (err == -1) throw ("fcntl");
    err = 1;
    err = setsockopt(fdsock, SOL_SOCKET, SO_REUSEADDR, &err, sizeof(err));
    if (err == -1) throw ("setsockopt");

    return fdsock;
}

void our_listen(const SOCKET_FD & fdsock)
{
    err = listen(fdsock, BACK_LOG);
    if (err == -1) throw ("listen");
}

void accepting(WebServ & webserv, const size_t & index)
{
    std::cout << ANSI_GREEN;
    std::cout << "... accepting ..." << std::endl;
    std::cout << ANSI_RESET;

    Connection & conn = webserv.get_connection(index);
    const SOCKET_POLL & socket_server = conn.get_socket();

    SOCKET_FD fdsock_client = accept(socket_server.fd, NULL, NULL);
    if (fdsock_client == -1) return;

    err = fcntl(fdsock_client, F_SETFL, O_NONBLOCK);
    if (err == -1) { close(fdsock_client); return; }
    err = 1;
    err = setsockopt(fdsock_client, SOL_SOCKET, SO_REUSEADDR, &err, sizeof(err));
    if (err == -1) { close(fdsock_client); return; }

    webserv.add_connection(!LISTEN_ENABLE, fdsock_client, conn._srvs);
}

void receiving(WebServ & webserv, const size_t & index)
{
    std::cout << ANSI_GREEN;
    std::cout << "... receiving ..." << std::endl;
    std::cout << ANSI_RESET;

    Connection & conn = webserv.get_connection(index);
    const SOCKET_POLL & socket_client = conn.get_socket();
    Request & req = *conn._req;

    int number_of_bytes = recv(socket_client.fd, buffer, BUFFER_SIZE, 0);
    if (number_of_bytes == 0 || number_of_bytes == -1) webserv.remove_connection(index);
    else if (req.concatenate(std::string(buffer, number_of_bytes)))
        serving(webserv, index);
}

void sending(WebServ & webserv, const size_t & index)
{
    std::cout << ANSI_GREEN;
    std::cout << "... sending ..." << std::endl;
    std::cout << ANSI_RESET;

    Connection & conn = webserv.get_connection(index);
    const SOCKET_POLL & socket_client = conn.get_socket();
    Response & res = *conn._res;

    size_t length = res.extract();
    int number_of_bytes = send(socket_client.fd, buffer, length, 0);
    if (number_of_bytes == -1) webserv.remove_connection(index);
    res.seek_back(length - number_of_bytes);
    if (res.is_done()) webserv.remove_connection(index);
}

void serving(WebServ & webserv, const size_t & index)
{
    std::cout << ANSI_GREEN;
    std::cout << "... serving ..." << std::endl;
    std::cout << ANSI_RESET;

    Connection & conn = webserv.get_connection(index);

    conn._req->print();
    conn._res->serving(*conn._srv, conn._loc);

    conn.flip_read_to_write();
}
