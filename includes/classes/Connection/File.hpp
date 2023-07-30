#ifndef FILE_HPP
#define FILE_HPP

#include "prototypes.hpp"


struct File {
    std::string	*fullpath;
    std::string uri;
    std::string filename;
    std::string extention;
    std::string pathInfo;
    bool            existance;
    bool            directory;
    bool            cgi;
    const Location  *loc;

    File(std::string *path, const std::string &reqUri, const Location *location);

    bool    fileExists();
    bool    isDirectory();
    void    extractFileName();
    void    separatePathInfo();
    void    extractExtention();
    bool    nameHasSlash();
};

#endif //FILE_HPP 