/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdOper.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdidelot <fdidelot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 20:26:58 by fdidelot          #+#    #+#             */
/*   Updated: 2022/03/04 20:26:58 by fdidelot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

void	Command::_oper(std::stringstream& completeCommand, User& user) {

	std::string cmd = "OPER";
	std::string name;
	std::string pass;

	completeCommand >> name >> pass;
	if (name.empty() || pass.empty())
		sendCommand(user, 461, ERR_NEEDMOREPARAMS(cmd));
	if (user.setOperator(name, pass) == 0)
		sendCommand(user, 381, RPL_YOUREOPER());
	else
		sendCommand(user, 464, ERR_PASSWDMISMATCH());
}