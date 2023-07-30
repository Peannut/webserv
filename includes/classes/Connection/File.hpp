#ifndef FILE_HPP
#define FILE_HPP

#include "prototypes.hpp"


struct File {
    std::string	*fullpath;
    std::string uri;
    std::string filename;
    std::string extention;
    std::string pathInfo;
    bool            cgi;
    const Location  *loc;

    File(std::string *path, const std::string &reqUri, const Location *location);

    void    isDirectory();
    void    extractFileName();
    void    separatePathInfo();
    void    extractExtention();
    bool    nameHasSlash();
};

#endif //FILE_HPP 