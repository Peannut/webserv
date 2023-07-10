/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   includes.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwina <zwina@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 17:44:35 by zwina             #+#    #+#             */
/*   Updated: 2023/07/09 14:54:26 by zwina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_HPP
#define HEADER_HPP

// Includes
#include <iostream>
#include <fstream>
#include <sstream>
#include <locale>

#include <algorithm>
#include <iterator>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <set>

#include <utility>
#include <cstring>
#include <cerrno>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netdb.h>
#include <fcntl.h>
#include <poll.h>

#include "prototypes.hpp"

// Classes Definitions
#include "classes/Connection/Request.hpp"
#include "classes/Connection/Response.hpp"
#include "classes/Connection/Connection.hpp"
#include "classes/Config/Location.hpp"
#include "classes/Config/Server.hpp"
#include "classes/Config/Config.hpp"
#include "classes/WebServ.hpp"

#endif // HEADER_HPP
