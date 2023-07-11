/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwina <zwina@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 17:44:17 by zwina             #+#    #+#             */
/*   Updated: 2023/06/23 23:07:51 by zwina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include "prototypes.hpp"

struct Server
{
    // host
    // port
    // ...
    std::vector<Location> _loct;
};

#endif // SERVER_HPP
