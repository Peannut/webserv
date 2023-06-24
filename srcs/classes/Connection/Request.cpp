/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwina <zwina@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 15:03:22 by zwina             #+#    #+#             */
/*   Updated: 2023/06/24 15:03:23 by zwina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.hpp"

void Request::concatenate(const std::string & str)
{
    _req_raw.append(str);
}

std::string & Request::get_req_raw(void)
{
    return (_req_raw);
}
