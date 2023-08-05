/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   includes.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoukaddo <zoukaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 17:44:35 by zwina             #+#    #+#             */
/*   Updated: 2023/08/05 17:29:10 by zoukaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_HPP
#define HEADER_HPP

// Includes
#include <iostream>
#include <locale>
#include <utility>

#include <algorithm>
#include <iterator>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>
#include <set>

#include <cstdlib>
#include <cstring>
#include <cerrno>
#include <ctime>

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <dirent.h>
#include <netdb.h>
#include <fcntl.h>
#include <poll.h>

#include <ctime>

#include "prototypes.hpp"

#include <dirent.h>

// Classes Definitions
#include "classes/Config/Location.hpp"
#include "classes/Config/Server.hpp"
#include "classes/Config/Config.hpp"
#include "classes/Connection/Cgi.hpp"
#include "classes/Connection/Request.hpp"
#include "classes/Connection/Response.hpp"
#include "classes/Connection/Connection.hpp"
#include "classes/Connection/File.hpp"
#include "classes/WebServ.hpp"
#include "classes/Connection/File.hpp"

// #include "classes/Connection/Request.hpp"
// #include "classes/Connection/File.hpp"
// #include "classes/Connection/Response.hpp"
// #include "classes/Connection/Connection.hpp"
// #include "classes/Config/Location.hpp"
// #include "classes/Config/Server.hpp"
// #include "classes/Config/Config.hpp"
// #include "classes/Connection/Request.hpp"
// #include "classes/Connection/Cgi.hpp"
// #include "classes/Connection/Response.hpp"
// #include "classes/Connection/Connection.hpp"
// #include "classes/WebServ.hpp"

#endif // HEADER_HPP
