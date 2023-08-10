#include <unistd.h>
#include <stdio.h>

int main(int ac, char **argv, char **env) {
    char * const av[3] = {
        const_cast<char * const>("/usr/bin/php-cgi7.4"),
        const_cast<char * const>("/home/peanut/webserv/srcs/CGI/scripts/sm.php"),
        NULL
    };

    char * const envp[] = {
        const_cast<char * const>("DOCUMENT_ROOT=/home/peanut/webserv/srcs/CGI/scripts"),
        const_cast<char * const>("SCRIPT_FILENAME=/home/peanut/webserv/srcs/CGI/scripts/sm.php"),
        const_cast<char * const>("REQUEST_METHOD=GET"),
        const_cast<char * const>("QUERY_STRING="), // Set this if there's a query string
        const_cast<char * const>("HTTP_USER_AGENT=YourUserAgent"), // Optional HTTP headers
        NULL
    };
    if (execve("/usr/bin/php-cgi7.4", av, env) == -1) {
        perror("execve");
    }

    return 0;
}
