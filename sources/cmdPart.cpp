/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdPart.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 11:35:31 by psemsari          #+#    #+#             */
/*   Updated: 2022/02/17 16:27:04 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

void	Command::_part(std::stringstream& completeCommand, User& user)
{
	std::string toPart;
	Channel *channeltofind;

	while (completeCommand >> toPart)
	{
		channeltofind = user.getChannel(toPart);
		if (channeltofind == NULL)
		{
			if (user.getServer().getChannel(toPart) == NULL)
				sendCommand(user, ERRCODE_NOSUCHCHANNEL, ERR_NOSUCHCHANNEL(toPart));
			else
				sendCommand(user, ERRCODE_NOTONCHANNEL, ERR_NOTONCHANNEL(toPart));
		}
		else
		{
			user.removeChannel(toPart);
			user.getServer().eraseChannel(toPart);
			sendCommand(user, PONG, completeCommand.str());
		}
	}
}
