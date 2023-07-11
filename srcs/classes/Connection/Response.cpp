/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynuiga <ynuiga@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 15:03:17 by zwina             #+#    #+#             */
/*   Updated: 2023/07/11 11:11:36 by ynuiga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.hpp"

Response::Response(int code, const std::string& message, const std::string& type, const std::string& body)
        : statusCode(code), statusMessage(message), contentType(type), content(body) {}

