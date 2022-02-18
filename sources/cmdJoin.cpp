/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdJoin.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 17:23:09 by psemsari          #+#    #+#             */
/*   Updated: 2022/02/18 12:36:02 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

void	Command::_join(std::stringstream& completeCommand, User& user) {

	std::string toJoin;
	while (completeCommand >> toJoin)
	{
		std::cout << "OUTPUT toJoin = " << toJoin << std::endl;
		Channel* channel = user.getServer().getChannel(toJoin);
		if (channel == NULL)
		{
			user.getServer().createChannel(toJoin);
			channel = user.getServer().getChannel(toJoin);
			channel->setName(toJoin);
		}
		channel->addToChannel(&user);//euheuheueh
		user.addChannel(channel);
	}
	sendCommand(user, PONG, completeCommand.str() + "\r\n");
}
