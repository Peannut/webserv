#ifndef FILE_HPP
#define FILE_HPP

#include "prototypes.hpp"


struct File {
    std::string	*fullpath;
    std::string uri;
    std::string filename;
    std::string extention;
    std::string pathWithoutInfo;
    std::string pathInfo;
    const Location  *loc;
    bool            cgi;

    File(std::string *path, const std::string &reqUri, const Location *location);

    void    extractFileName();
    void    separatePathInfo();
    void    extractExtention(size_t &);
    void    fileCgiSupport();
    //getters
};

#endif //FILE_HPP 