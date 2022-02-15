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
#include <iomanip>

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
std::string	Command::errMode(User& user) const {

	std::string toReturn;
	std::string charS(1, user.getErrModeChar());

	toReturn += ERR_UNKNOWNMODE(charS);
	// if (isInChannel(user))
	// 	add ERR_UNKNOWNMODE_END;
	return (toReturn);
}

void	Command::sendCommand(User& user, int msgId) const {

	std::stringstream numberStream;
	std::string toSend;
	std::string servName = static_cast<std::string>(SERV_NAME);
	std::string servCreation = static_cast<std::string>(CREATION_DATE);

	int fd = user.getFd();
	if (msgId != PONG)
	{
		numberStream << std::setw(3) << std::setfill('0') << msgId;
		toSend += RPL_MESSAGE(servName, numberStream.str(), user.getNick());
	}
	switch (msgId)
	{
		case 1:
			toSend += RPL_WELCOME(user.getNick());
			break;
		case 2:
			toSend += RPL_YOURHOST(servName, SERV_VERSION);
			break;
		case 3:
			toSend += RPL_CREATED(servCreation);
			break;
		case 4:
			toSend += RPL_MYINFO(servName, SERV_VERSION);
			break;
		case MODE:
			toSend += "+" + user.getModes();
			break;
		case PONG:
			toSend += PONG_MSG(servName);
			break;
		case UNKNOWN_MODE:
			toSend += errMode(user);
			break;
	}
	toSend += "\r\n";
	send(fd, toSend.c_str(), toSend.size(), SEND_OPT);
}

void	Command::sendStartMsgs(User& user) const {

	for (int i = 1; i < 5; i++)
		sendCommand(user, i);
}

void	Command::launchCommand(std::stringstream& completeCommand, User& user) {

	void	(Command::*command[NB_COMMAND])(std::stringstream&, User&) = {
		&Command::_pass,
		&Command::_nick,
		&Command::_user,
		&Command::_cap,
		&Command::_mode,
		&Command::_join,
		&Command::_ping,
		&Command::_privmsg
	};
	std::string commandId[NB_COMMAND] = {
		"PASS",
		"NICK",
		"USER",
		"CAP",
		"MODE",
		"JOIN",
		"PING",
		"PRIVMSG"
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
