#ifndef PROTOTYPES_HPP
#define PROTOTYPES_HPP

// Defines
#define UNUSED(x) (void)(x) // unused variable
#define SOCKET_POLL struct pollfd
#define SOCKET_FD int
#define LISTEN_ENABLE true // the type of connection, is it a server socket (aka. listen) or a client socket
#define POLL_TIME 0 // the time that poll() waits in milliseconds
#define BACK_LOG 10 // one socket can handle BACK_LOG number of connection
#define BUFFER_SIZE (size_t)1024 // the size of the receiving the sending buffer

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
void                our_poll            (std::vector<SOCKET_POLL> & sockets);
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


#endif // PROTOTYPES_HPP
