/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoukaddo <zoukaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 19:14:14 by zoukaddo          #+#    #+#             */
/*   Updated: 2023/06/17 11:18:23 by zoukaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

int main(int ac, char **av)
{
	if (ac  != 2)
	{
		std::cerr << "check ur arguments" << std::endl;
		return (1);
	}
	// Webserver web;
	// try
	// {
	// 	web.setupconfig(av[1]);

	// }
	// catch(const std::exception& e)
	// {
	// 	std::cerr << e.what() << '\n';
	// }
	
	return (0);
}