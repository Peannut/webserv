#ifndef PROTOTYPES_HPP
#define PROTOTYPES_HPP

// Defines
#define UNUSED(x) (void)(x) // unused variable
#define SOCKET int
#define KQUEUE int
#define POLLTIMEOUT 100 // in milliseconds

// This is the declaration, the definition is in the main.cpp file
extern int err;

// The declarations of the structs
struct Webserv;
struct Config;
struct Server;
struct Location;
struct Connection;
struct Request;
struct Response;

// The declarations of the functions
int create_binded_socket(void);

#endif // PROTOTYPES_HPP
