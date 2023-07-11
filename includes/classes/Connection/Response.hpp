#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include "prototypes.hpp"

struct Response
{
    std::string _res_raw;
    size_t _offset;

    size_t subtract(const size_t & number_of_bytes);
    std::string & get_res_raw(void);
    const char * get_res_raw_shifted(void);
    void serving();
};

#endif // RESPONSE_HPP
