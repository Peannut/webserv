/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwina <zwina@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 17:44:22 by zwina             #+#    #+#             */
/*   Updated: 2023/06/23 23:45:27 by zwina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_HPP
#define REQUEST_HPP

#include "prototypes.hpp"

struct Request
{
    std::string _req_raw;

    void concatenate(const std::string & str);
    std::string & get_req_raw(void);
};

#endif // REQUEST_HPP
