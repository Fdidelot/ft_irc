/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdNames.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 15:07:52 by psemsari          #+#    #+#             */
/*   Updated: 2022/02/18 15:29:25 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

void	Command::_names(std::stringstream& completeCommand, User& user)
{

	std::string toSearch;
	std::string ret;
	completeCommand >> toSearch;
	Channel::users_list& list = user.getServer().getChannel(toSearch)->getList();

	Channel::users_list::iterator it = list.begin();
	Channel::users_list::iterator ite = list.end();
	for (;it != ite; it++)
	{
		ret += " " + (*it)->getNick();
	}
	sendCommand(user, RPLCODE_NAMREPLY, RPL_NAMREPLY(toSearch, ret));
	sendCommand(user, RPLCODE_ENDOFNAMES, RPL_ENDOFNAMES());
}
