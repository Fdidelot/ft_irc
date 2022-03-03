/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdidelot <fdidelot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 15:53:47 by fdidelot          #+#    #+#             */
/*   Updated: 2022/03/03 19:20:12 by fdidelot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

// Server* g_serv;

// void	sigint_handler(int sig_value)
// {
// 	std::map<int, User>::iterator it = g_serv->getUsers().begin();
// 	std::map<int, User>::iterator ite = g_serv->getUsers().end();

// 	for (;it != ite; it++)
// 		it->second.getServer().endConnection(it->second.getFd());
// 	exit(sig_value);
// }

void	sigpipe_handler(int sig_value)
{
	(void)sig_value;
}

int main(int ac, char **av)
{
	// signal(SIGINT, sigint_handler);
	// signal(SIGQUIT, sigint_handler);
	signal(SIGPIPE, sigpipe_handler);
	try
	{
		if (ac != 3)
			throw Server::badArgumentsCountException();

		Server ircServer;
		// g_serv = &ircServer;

		ircServer.launchServer(av[1], av[2]);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	return (0);
}
