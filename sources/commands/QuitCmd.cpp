/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdQuit.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdidelot <fdidelot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 20:28:05 by fdidelot          #+#    #+#             */
/*   Updated: 2022/03/04 20:28:06 by fdidelot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

void    Command::_quit(std::stringstream& completeCommand, User& user) {

	std::string arg;
	std::string reply;
	Server::Channel_map_it it = user.getServer().getChannelMap().begin();
	Server::Channel_map_it it_to_erase;
	Server::Channel_map_it ite = user.getServer().getChannelMap().end();

	completeCommand >> arg;
	reply = "QUIT " + arg + "\r\n";

	while (it != ite)
	{
		it->second.removeFromChannel(&user);
		if (it->second.getList().empty())
		{
			it_to_erase = it;
			it++;
			user.getServer().eraseChannel(it_to_erase->first);
		}
		else
			it++;
		if (user.getServer().getChannelMap().size() == 0)
			break ;
	}
	send(user.getFd(), reply.c_str(), reply.size(), SEND_OPT);
	user.setIsEnded(true);
}
