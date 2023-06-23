#ifndef SERVER_HPP
#define SERVER_HPP

#include "prototypes.hpp"

struct Server
{
    // host
    // port
    // ...
    size_t _number_of_locations;
    std::vector<Location> _loct;
};

#endif // SERVER_HPP
