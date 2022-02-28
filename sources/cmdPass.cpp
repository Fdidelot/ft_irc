/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdPass.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdidelot <fdidelot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 17:24:34 by psemsari          #+#    #+#             */
/*   Updated: 2022/02/18 19:45:22 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

void	Command::_pass(std::stringstream& completeCommand, User& user) {

	user.setPassGiven(true);
	std::cout << "Pass command :" << completeCommand.str() << std::endl;
	if (!user.getUserOrNickCmd())
	{
		std::string pass;
		std::string cmd = "PASS";
		completeCommand >> pass;
		if (pass.empty())
		{
			sendCommand(user, 461, ERR_NEEDMOREPARAMS(cmd));
		}
		if (pass != user.getServer().getPassword())
			user.setIsEnded(true);
	}
	else
	{
		sendCommand(user, 462, ERR_ALREADYREGISTRED());
	}
}
