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
void	Command::_pass(std::stringstream& completeCommand) {

	std::cout << "exec pass" << std::endl;
	(void)completeCommand;
}


void	Command::_nick(std::stringstream& completeCommand) {

	std::cout << "exec nick" << std::endl;
	(void)completeCommand;
}

void	Command::_user(std::stringstream& completeCommand) {

	std::cout << "exec user" << std::endl;
	(void)completeCommand;
}

void	Command::_cap(std::stringstream& completeCommand) {

	std::cout << "exec cap" << std::endl;
	(void)completeCommand;
}

void	Command::launchCommand(std::stringstream& completeCommand) {

	void	(Command::*command[NB_COMMAND])(std::stringstream&) = {
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
			(this->*command[i])(completeCommand);
			break;
		}
	}
	if (i == NB_COMMAND)
		std::cout << "Unknown command" << std::endl;
}
