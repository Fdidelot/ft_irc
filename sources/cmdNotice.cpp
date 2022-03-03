/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdNotice.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdidelot <fdidelot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 15:56:08 by psemsari          #+#    #+#             */
/*   Updated: 2022/03/03 21:12:07 by fdidelot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

void	Command::_notice(std::stringstream& completeCommand, User& user){

	std::string target;
	completeCommand >> target;
	std::cout << "OUTPUT target = " << target << std::endl;
	User *user_ptr = user.getServer().getUser(target);
	std::cout << completeCommand.str() << std::endl;
	if (target[0] == '#')
	{
		Channel* chan_ptr = user.getServer().getChannel(target);
		std::cout << "ptr = " << chan_ptr << std::endl;
		if (chan_ptr != NULL)
			chan_ptr->sendToChannel(":" + user.getNickHost() + " " + completeCommand.str() + "\r\n", *this, user.getFd());
	}
	else
	{
		std::cout << completeCommand.str() << std::endl;
		if (user_ptr != NULL)
			sendDirect(*user_ptr, PONG, ":" + user.getNickHost() + " " + completeCommand.str() + "\r\n");
	}
}
