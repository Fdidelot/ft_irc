/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdPrivmsg.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 17:25:17 by psemsari          #+#    #+#             */
/*   Updated: 2022/02/15 17:41:35 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

void	Command::_privmsg(std::stringstream& completeCommand, User& user){

	//:prefix PRIVMSG user/#target | message suitemessage
	//send((*it)->getFd(), str.c_str(), str.size(), NULL);
	(void)user;
	std::string tmp;
	completeCommand >> tmp;
	std::cout << "OUTPUT tmp = " << tmp << std::endl;
	if (tmp[0] == '#')
		;//ejifjes
}
