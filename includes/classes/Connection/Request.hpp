#ifndef REQUEST_HPP
#define REQUEST_HPP

#include "prototypes.hpp"

enum Modes {
    method_m,
    path_m,
    encoding_m,
    query_key_m,
    query_val_m,
    version_m,

    field_CRLF_m,
    field_key_m,
    field_val_m,
    field_last_CRLF_m,

    body_content_m,
    body_length_m,
    body_length_CRLF_m,
    body_chunk_m,
    body_chunk_CRLF_m,

    error_m,
    success_m,
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
    short _error;
    Methods _method;
    std::string _uri;
    std::string _path;
    std::string _query;
    std::vector<std::pair<std::string, std::string> > _queries;
    std::string _version;
    std::map<std::string, std::string> _fields;
    std::string _body;
    
    private:
    Modes _mode;
    Transfers _transfer;
    size_t _transfer_content_max_len;
    size_t _transfer_content_len;
    size_t _transfer_chunk_len;
    std::string __tmp1;
    std::string __tmp2;

    Connection & _conn;

    public:
    Request(Connection & conn);
    bool concatenate(const std::string & buffer);
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
    void encoding_mode(const char & c);
    void query_key_mode(const char & c);
    void query_val_mode(const char & c);
    void version_mode(const char & c);
    void field_CRLF_mode(const char & c);
    void field_key_mode(const char & c);
    void field_val_mode(const char & c);
    void field_last_CRLF_mode(const char & c);
    void matchingServer(const std::string & host);
    void matchingLocation();
    size_t body_content_mode(const std::string & buffer, const size_t & i);
    void body_length_mode(const char & c);
    void body_length_CRLF_mode(const char & c);
    void body_chunk_mode(const char & c);
    void body_chunk_CRLF_mode(const char & c);
    void set_transfer(const Transfers & tr);
    void set_error(const short & e);
};

#endif // REQUEST_HPP
