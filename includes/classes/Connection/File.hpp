#ifndef FILE_HPP
#define FILE_HPP

#include "prototypes.hpp"


struct File {
    std::string	*fullpath;
    std::string uri;
    std::string filename;
    std::string extention;
    std::string pathInfo;
    bool            existing;
    bool            directory;
    bool            cgi;
    bool            endWithSlash;
    const Location  *loc;

    File(std::string *path, const std::string &reqUri, const Location *location);

    void    setFileInformation();
    bool    fileExists();
    bool    isDirectory();
    bool    nameHasSlash();
    void    concatinateIndexFile();
    void    extractFileName();
    void    separatePathInfo();
    void    extractExtention();
    bool	fileCgiSupport();
};

#endif //FILE_HPP 