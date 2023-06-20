/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoukaddo <zoukaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 19:14:14 by zoukaddo          #+#    #+#             */
/*   Updated: 2023/06/20 11:05:42 by zoukaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/webserv.hpp"

int main(int ac, char **av)
{
	Web web;
	if (ac  != 2)
	{
		std::cerr << "check ur arguments" << std::endl;
		return (1);
	}
	try
	{
		web.setupconfig(av[1]);

	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	
	return (0);
}