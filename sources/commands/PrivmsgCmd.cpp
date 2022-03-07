/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdPrivmsg.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdidelot <fdidelot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 20:27:47 by fdidelot          #+#    #+#             */
/*   Updated: 2022/03/04 20:27:54 by fdidelot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

void	Command::_privmsg(std::stringstream& completeCommand, User& user){

	std::string target;
	completeCommand >> target;
	if (target[0] == '#')
	{
		Channel* chan_ptr = user.getChannel(target);
		if (chan_ptr == NULL)
			sendCommand(user, ERRCODE_CANNOTSENDTOCHAN, ERR_CANNOTSENDTOCHAN(target));
		else
			chan_ptr->sendToChannel(":" + user.getNick() + " " + completeCommand.str() + "\r\n", *this, user.getFd());
	}
	else
	{
		User *user_ptr = user.getServer().getUser(target);
		std::cout << completeCommand.str() << std::endl;
		if (user_ptr == NULL)
			sendCommand(user, ERRCODE_NOSUCHNICK, ERR_NOSUCHNICK(target));
		else
			sendDirect(*user_ptr, PONG, ":" + user.getNick() + " " + completeCommand.str() + "\r\n");
	}
}
