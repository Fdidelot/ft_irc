/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdPass.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdidelot <fdidelot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 17:24:34 by psemsari          #+#    #+#             */
/*   Updated: 2022/02/16 18:41:55 by fdidelot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

void	Command::_pass(std::stringstream& completeCommand, User& user) {

	std::cout << "Pass command :" << completeCommand.str() << std::endl;
	if (!user.getUserOrNickCmd())
	{
		std::string pass;
		std::string cmd = "PASS";
		completeCommand >> pass;
		std::cout << "Password is :" << pass << std::endl;
		if (pass.empty())
		{
			sendCommand(user, 461, ERR_NEEDMOREPARAMS(cmd));
		}
		if (pass != user.getServer().getPassword())
			user.getServer().endConnection(user.getFd());
	}
	else
	{
		sendCommand(user, 462, ERR_ALREADYREGISTRED());
	}
}
