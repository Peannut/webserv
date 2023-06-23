#ifndef PROTOTYPES_HPP
#define PROTOTYPES_HPP

// This is the declaration, the definition is in the main.cpp file
extern int err;

// Defines
#define UNUSED(x) (void)(x) // unused variable
#define SOCKET int
#define KQUEUE int
#define POLLTIMEOUT 100 // in milliseconds

// The declarations of the structs
struct Webserv;
struct Config;
struct Server;
struct Location;
struct Connection;
struct Request;
struct Response;

// The declarations of the functions
struct addrinfo *   our_getaddrinfo (const char *hostname, const char *servname);
int                 our_bind        (struct addrinfo *records);
void                our_listen      (const int &fdsock, const int &backlog);
SOCKET              our_socket      (const int &domain, const int &type, const int &protocol);

#endif // PROTOTYPES_HPP
