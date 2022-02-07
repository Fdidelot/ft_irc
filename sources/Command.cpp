/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdidelot <fdidelot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 21:44:44 by fdidelot          #+#    #+#             */
/*   Updated: 2021/12/07 19:18:07 by fdidelot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

/************************************************************/
/*					Constructor/Destructor					*/
/************************************************************/
Command::Command(std::string commandName) :
											_type(commandName) {

	return ;
}

Command::~Command(void) {

	return ;
}

/************************************************************/
/*						Operators							*/
/************************************************************/

/************************************************************/
/*					Members functions						*/
/************************************************************/
void	Command::_pass(std::stringstream& completeCommand, User& user) {

	(void)completeCommand; (void)user;
	std::cout << "exec pass" << std::endl;
}


void	Command::_nick(std::stringstream& completeCommand, User& user) {

	std::string nickname;

	completeCommand >> nickname;
	user.setNickname(nickname);
}

void	Command::_user(std::stringstream& completeCommand, User& user) {

	(void)completeCommand; (void)user;
	std::cout << "exec user" << std::endl;
}

void	Command::_cap(std::stringstream& completeCommand, User& user) {

	(void)completeCommand;(void)user;
	std::cout << "cap cmd" << std::endl;
}

void	Command::launchCommand(std::stringstream& completeCommand, User& user) {

	void	(Command::*command[NB_COMMAND])(std::stringstream&, User&) = {
		&Command::_pass,
		&Command::_nick,
		&Command::_user,
		&Command::_cap
	};
	std::string commandId[NB_COMMAND] = {
		"PASS",
		"NICK",
		"USER",
		"CAP"
	};

	int	i;
	for (i = 0; i < NB_COMMAND; i++)
	{
		if (_type == commandId[i])
		{
			(this->*command[i])(completeCommand, user);
			break;
		}
	}
	if (i == NB_COMMAND)
		std::cout << "Unknown command" << std::endl;
}
