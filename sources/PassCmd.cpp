/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdPass.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdidelot <fdidelot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 20:27:33 by fdidelot          #+#    #+#             */
/*   Updated: 2022/03/04 20:27:33 by fdidelot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

void	Command::_pass(std::stringstream& completeCommand, User& user) {

	if (!user.getUserOrNickCmd() && !user.getPassGiven())
	{
		std::string pass;
		std::string cmd = "PASS";
		completeCommand >> pass;
		if (pass.empty())
		{
			sendCommand(user, ERRCODE_NEEDMOREPARAMS, ERR_NEEDMOREPARAMS(cmd));
		}
		if (pass != user.getServer().getPassword())
			user.setIsEnded(true);
	}
	else
	{
		sendCommand(user, ERRCODE_ALREADYREGISTRED, ERR_ALREADYREGISTRED());
	}
	user.setPassGiven(true);
}
