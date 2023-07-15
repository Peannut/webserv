/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoukaddo <zoukaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 15:03:17 by zwina             #+#    #+#             */
/*   Updated: 2023/07/15 16:02:07 by zoukaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.hpp"

size_t Response::subtract(const size_t & number_of_bytes)
{
    if (number_of_bytes + _offset >= _res_raw.size()) _offset = _res_raw.size();
    else _offset += number_of_bytes;

    return (_res_raw.size() - _offset);
}

#include "includes.hpp"

void Response::serving(const Server &server, const Location *loc, const std::string &loc_Path) {
        Response response();
        if (checkRequestError(response.request)) {
        response.Headers = buildErrorResponseH(req);
        response.content = buildErrorResponseB(req);
        return 1;
	}

}
