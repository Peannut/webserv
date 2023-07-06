/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwina <zwina@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 15:03:17 by zwina             #+#    #+#             */
/*   Updated: 2023/07/06 15:06:10 by zwina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.hpp"

size_t Response::subtract(const size_t & number_of_bytes)
{
    if (number_of_bytes + _offset >= _res_raw.size()) _offset = _res_raw.size();
    else _offset += number_of_bytes;

    return (_res_raw.size() - _offset);
}

std::string & Response::get_res_raw(void)
{
    return (_res_raw);
}

const char * Response::get_res_raw_shifted(void)
{
    return (_res_raw.data() + _offset);
}

void Response::serving()
{
    _res_raw.assign(response + "HH");
    std::cout << "RESPONSE = ["<<_res_raw<<']' << std::endl;
}
