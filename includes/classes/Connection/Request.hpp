#ifndef REQUEST_HPP
#define REQUEST_HPP

#include "prototypes.hpp"

enum Modes {
    method_m,           // 0
    path_m,             // 1
    query_key_m,        // 2
    query_val_m,        // 3
    version_m,          // 4

    field_CRLF_m,       // 5
    field_key_m,        // 6
    field_val_m,        // 7
    field_last_CRLF_m,  // 8

    body_content_m,     // 9
    body_length_m,      // 10
    body_length_CRLF_m, // 11
    body_chunk_m,       // 12
    body_chunk_CRLF_m,  // 13

    error_m,            // 14
    success_m,          // 15
};

enum Errors {
    code_400_e,     // Bad Request
    code_501_e,     // Not Implemented
    code_426_e,     // Upgrade Required
    code_505_e,     // HTTP Version Not Supported
    code_411_e,     // Length Required
    code_415_e,     // Unsupported Media Type
    code_413_e,     // Content Too Large
    code_404_e,     // Not Found
    none_e,
};

enum Transfers {
    content_tr,
    chunk_tr,
    none_tr,
};

enum Methods {
    GET_method,
    POST_method,
    DELETE_method,
    none_method,
};

struct Request
{
    public:
    Errors _error;
    Methods _method;
    std::string _uri;
    std::string _path;
    std::string _query;
    std::vector<std::pair<std::string, std::string> > _queries;
    std::string _version;
    std::map<std::string, std::string> _fields;
    std::string _body;

    private:
    std::string _message; // REMOVE_THIS
    Modes _mode;
    Transfers _transfer;
    size_t _transfer_content_max_len;
    size_t _transfer_content_len;
    size_t _transfer_chunk_len;
    std::string __tmp1;
    std::string __tmp2;

    public:
    Request();
    bool concatenate(const std::string & buffer);
    void serving(Connection & conn);
    const Methods & get_method();
    const std::string & get_uri();
    const std::string & get_path();
    const std::string & get_queries();
    const std::pair<std::string, std::string> & get_query(const size_t & index);
    const std::string & get_version();
    const std::pair<std::string, std::string> get_fields(const std::string & str);
    const std::string & get_body();
    void set_max_len(const size_t & n);

    private:
    void method_mode(const char & c);
    void path_mode(const char & c);
    void query_key_mode(const char & c);
    void query_val_mode(const char & c);
    void version_mode(const char & c);
    void field_CRLF_mode(const char & c);
    void field_key_mode(const char & c);
    void field_val_mode(const char & c);
    void field_last_CRLF_mode(const char & c);
    void body_content_mode(const char & c);
    void body_length_mode(const char & c);
    void body_length_CRLF_mode(const char & c);
    void body_chunk_mode(const char & c);
    void body_chunk_CRLF_mode(const char & c);
    void set_transfer(const Transfers & tr);
    void set_error(const Errors & e);
};

#endif // REQUEST_HPP
