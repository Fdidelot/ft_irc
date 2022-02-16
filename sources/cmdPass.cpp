/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdPass.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 17:24:34 by psemsari          #+#    #+#             */
/*   Updated: 2022/02/15 17:24:50 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

void	Command::_pass(std::stringstream& completeCommand, User& user) {

	if (!user.getNick().empty() && !user.getUserOrNickCmd())
	{
		std::string pass;
		std::string cmd = "PASS";
		completeCommand >> pass;
		if (!pass.empty())
			sendCommand(user, 462, ERR_NEEDMOREPARAMS(cmd));
		std::cout << "Pass: " << pass << std::endl;
		if (pass != user.getServer().getPassword())
			user.getServer().endConnection(user.getFd());
	}
	else
	{
		sendCommand(user, 461, ERR_ALREADYREGISTRED());
	}
}
