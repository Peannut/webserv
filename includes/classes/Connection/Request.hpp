/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwina <zwina@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 17:44:22 by zwina             #+#    #+#             */
/*   Updated: 2023/07/06 12:14:28 by zwina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_HPP
#define REQUEST_HPP

#include "prototypes.hpp"

struct Request
{
    std::string _req_raw;
    std::string _method;
    std::string _path;
    std::string _version;
    std::vector<std::pair<std::string, std::string> > _headers;
    std::string _body;

    std::string & get_req_raw(void);
    void concatenate(const std::string & str);
    void serving();
};

#endif // REQUEST_HPP
