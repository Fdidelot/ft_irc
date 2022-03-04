/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdidelot <fdidelot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 15:53:47 by fdidelot          #+#    #+#             */
/*   Updated: 2022/03/04 16:59:46 by fdidelot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"


// kill ourself with /kill

// void	shutdownServer(int sigId)
// {
// 	if (sigId == SIGQUIT || sigId == SIGINT)
// 	{
// 		Server *tmp;
// 		tmp = (Server *)data;
// 		deleteAllUsers(tmp, tmp->getUsers());
// 		if (tmp->getAI() != NULL)
// 			freeaddrinfo(tmp->getAI());
// 		if (tmp->getListener() != -1)
// 			close(tmp->getListener());
// 		tmp->~Server();
// 		exit (0);
// 	}
// }

Server* g_serv;

void	sigintquit_handler(int sig_value)
{
	std::map<int, User>::iterator it = g_serv->getUsers().begin();
	std::map<int, User>::iterator ite = g_serv->getUsers().end();

	for (;it != ite; it++)
		g_serv->endConnection(it->second.getFd());
	if (g_serv->getAi() != NULL)
		freeaddrinfo(g_serv->getAi());
	exit(sig_value);
}

int main(int ac, char **av)
{
	signal(SIGINT, sigintquit_handler);
	signal(SIGQUIT, sigintquit_handler);
	signal(SIGPIPE, SIG_IGN);
	try
	{
		if (ac != 3)
			throw Server::badArgumentsCountException();

		Server ircServer;
		g_serv = &ircServer;

		ircServer.launchServer(av[1], av[2]);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	return (0);
}
