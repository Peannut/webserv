/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynuiga <ynuiga@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 17:44:22 by zwina             #+#    #+#             */
/*   Updated: 2023/07/11 12:30:25 by ynuiga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_HPP
#define REQUEST_HPP

#include "prototypes.hpp"
#include "includes.hpp"

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
    code_405_e,     // Method Not Allowed
    code_505_e,     // HTTP Version Not Supported
    code_411_e,     // Length Required
    code_501_e,     // Not Implemented
    none_e,
};

enum Transfers {
    content_tr,
    chunk_tr,
    none_tr,
};

enum Methods {
    get_method,
    post_method,
    delete_method,
    none_method,
};

struct Request
{
    /// @brief ///
    Modes _mode;
    Errors _error;
    Transfers _transfer;
    std::string _message; // REMOVE_THIS
    /// @brief ///
    Methods _method;
    std::string _uri;
    std::string _path;
    std::vector<std::pair<std::string, std::string> > _queries;
    std::string _version;
    std::map<std::string, std::string> _fields;
    std::string _body;
    /// @brief ///
    // size_t _transfer_content_len;
    // size_t _transfer_chunk_len;
    // std::string __tmp1;
    // std::string __tmp2;

    // Request();
    // bool concatenate(const std::string & buffer);
    // void serving();

    // void method_mode(const char & c);
    // void path_mode(const char & c);
    // void query_key_mode(const char & c);
    // void query_val_mode(const char & c);
    // void version_mode(const char & c);

    // void field_CRLF_mode(const char & c);
    // void field_key_mode(const char & c);
    // void field_val_mode(const char & c);
    // void field_last_CRLF_mode(const char & c);

    // void body_content_mode(const char & c);
    // void body_length_mode(const char & c);
    // void body_length_CRLF_mode(const char & c);
    // void body_chunk_mode(const char & c);
    // void body_chunk_CRLF_mode(const char & c);

    // void setTransferContent();
    // void setTransferChunk();
    // void setError(const Errors & e);
};

#endif // REQUEST_HPP
