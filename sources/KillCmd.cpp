/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdKill.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdidelot <fdidelot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 20:25:59 by fdidelot          #+#    #+#             */
/*   Updated: 2022/03/04 20:25:59 by fdidelot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

void	Command::_kill(std::stringstream& completeCommand, User& user) {

	std::string cmd = "KILL";
	std::string nick;
	std::string message;
	User *target;

	completeCommand >> nick;
	completeCommand >> message;
	if (nick == user.getNick())
	{
		user.setIsEnded(true);
		user.getServer().setUnavalaibleName(nick);
		return ;
	}
	if (user.getMode('o') == false)
	{
		sendCommand(user, ERRCODE_NOPRIVILEGES, ERR_NOPRIVILEGES());
		return ;
	}
	if (nick.empty() == true || message.empty())
	{
		sendCommand(user, ERRCODE_NEEDMOREPARAMS, ERR_NEEDMOREPARAMS(cmd));
		return ;
	}
	if (nick == SERV_NAME)
	{
		sendCommand(user, ERRCODE_CANTKILLSERVER, ERR_CANTKILLSERVER());
		return ;
	}
	message.erase(0, 1);
	target = user.getServer().findByNickName(user, nick);
	if (!target)
	{
		sendCommand(user, ERRCODE_NOSUCHNICK, ERR_NOSUCHNICK(nick));
		return ;
	}
	sendDirect(*target, PONG, "You have been killed because: " + message + "\r\n");
	user.getServer().setUnavalaibleName(nick);
	target->setIsEnded(true);

}