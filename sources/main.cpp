/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdidelot <fdidelot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 15:53:47 by fdidelot          #+#    #+#             */
/*   Updated: 2022/03/04 21:42:55 by fdidelot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server* g_serv;

//	affichage dans Server et dans user.cpp execcommand
//	changer nom des fichiers, mettre dans un dossier
//	channel operations
//	verifier les .hpp pour mettre en ordre

void	sigintquit_handler(int sig_value) {

	std::map<int, User>::iterator it = g_serv->getUsers().begin();
	std::map<int, User>::iterator it_to_erase;
	std::map<int, User>::iterator ite = g_serv->getUsers().end();

	g_serv->getUnavalaibleNames().clear();
	g_serv->getChannelMap().clear();
	while (it != ite)
	{
		it_to_erase = it;
		it++;
		g_serv->endConnection(it_to_erase->second.getFd());
	}
	if (g_serv->getListener() != -1)
		close(g_serv->getListener());
	if (g_serv->getAi() != NULL)
		freeaddrinfo(g_serv->getAi());
	exit(sig_value);
}

int main(int ac, char **av) {

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
