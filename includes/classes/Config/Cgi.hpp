/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cgi.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoukaddo <zoukaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 13:33:27 by zoukaddo          #+#    #+#             */
/*   Updated: 2023/07/16 20:28:44 by zoukaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGI_HPP
#define CGI_HPP

#include "prototypes.hpp"

struct Cgi{

	pid_t pid;
	char **env;
	std::string pathinfo;
	int	fd[2];
	int fd2[2];
};
#endif // ! CGI_HPP
