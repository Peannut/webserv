/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   our_functions.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwina <zwina@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 15:02:48 by zwina             #+#    #+#             */
/*   Updated: 2023/06/24 15:02:50 by zwina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.hpp"

struct addrinfo *our_getaddrinfo(const char *hostname, const char *servname)
{
    struct addrinfo *records;
    struct addrinfo hints;

    bzero(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    err = getaddrinfo(hostname, servname, &hints, &records);
    if (err) throw (err);

    for (struct addrinfo * tmp = records; tmp; tmp = tmp->ai_next)
    {
        std::cout << "=> port and address :\n";
        for (sa_family_t i = 0; i < tmp->ai_addr->sa_len; ++i) {
            if (i != 0) std::cout << " .";
            std::cout << std::setw(3) << (unsigned int)(unsigned char)tmp->ai_addr->sa_data[i];
        }
        std::cout << std::endl;
    }

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

        std::cerr << "\tbind() => " << strerror(errno) << std::endl;
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

    err = setsockopt(fdsock, SOL_SOCKET, SO_REUSEADDR, &err, sizeof(err));
    if (err == -1) throw ("setsockopt");

    return fdsock;
}

void our_listen(const SOCKET_FD & fdsock)
{
    err = listen(fdsock, BACK_LOG);
    if (err == -1) throw ("listen");
}

void our_poll(std::vector<SOCKET> & sockets)
{
    err = poll(sockets.data(), sockets.size(), POLL_TIME);
    if (err == -1) throw ("poll");
}

void accepting(WebServ & webserv, const size_t & index)
{
    SOCKET & socket_server = webserv.get_socket(index);
    struct sockaddr_storage client_address;
    socklen_t client_len = sizeof(client_address);

    SOCKET_FD fdsock_client = accept(socket_server.fd, (struct sockaddr *)&client_address, &client_len);
    if (fdsock_client == -1) throw ("accept");

    err = fcntl(fdsock_client, F_SETFL, O_NONBLOCK);
    if (err == -1) throw ("fcntl");

    err = setsockopt(fdsock_client, SOL_SOCKET, SO_REUSEADDR, &err, sizeof(err));
    if (err == -1) throw ("setsockopt");

    webserv.add_connection(!LISTEN_ENABLE, fdsock_client);

    char address_buffer[100];
    getnameinfo((struct sockaddr *)&client_address, client_len, address_buffer, sizeof(address_buffer), 0, 0, NI_NUMERICHOST);
    std::cout << "New connection from " << address_buffer << std::endl;
}

void receiving(WebServ & webserv, const size_t & index)
{
    const SOCKET & socket_client = webserv.get_socket(index);
    Request & req = webserv.get_connection(index).get_req();

    int number_of_bytes = recv(socket_client.fd, buffer, BUFFER_SIZE - 1, 0); // subtract one to leave a place for the '\0'
    if (number_of_bytes == -1) throw ("recv");

    if (number_of_bytes == 0) webserv.remove_connection(index);
    else { buffer[number_of_bytes] = '\0'; req.concatenate(buffer); }
}

void sending(WebServ & webserv, const size_t & index)
{
    const SOCKET & socket_client = webserv.get_socket(index);
    Response & res = webserv.get_connection(index).get_res();

    if (res.offset == 0) res._res_raw.assign(response + "HH"); // parsing the request and send it to the response

    const char * response_chunked = res.get_res_raw_shifted();
    const size_t response_chunked_len = std::min(strlen(response_chunked), BUFFER_SIZE);
    int number_of_bytes = send(socket_client.fd, response_chunked, response_chunked_len, 0);
    if (number_of_bytes == -1) throw ("send");

    size_t remaining_bytes = res.subtract(number_of_bytes);
    if (remaining_bytes == 0) webserv.remove_connection(index);
}
