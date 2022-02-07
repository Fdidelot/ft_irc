/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdidelot <fdidelot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 21:44:44 by fdidelot          #+#    #+#             */
/*   Updated: 2021/12/07 19:18:07 by fdidelot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.hpp"

/************************************************************/
/*					Constructor/Destructor					*/
/************************************************************/
User::User(void) :	_commandEnd(false), _commandBuf(""),
					_fd(-1), _nick("defaultNickname") {

	return ;
}

User::User(int fd) : _commandEnd(false), _commandBuf(""), _fd(fd) {

	return ;
}

User::~User(void) {

	return ;
}

/************************************************************/
/*						Operators							*/
/************************************************************/

/************************************************************/
/*					Getters/Setters							*/
/************************************************************/
/*						Getters								*/
bool	User::getCommandEnd(void) const {

	return (_commandEnd);
}

std::string User::getCommandBuf(void) const {

	return (_commandBuf);
}

int		User::getFd(void) const {

	return (_fd);
}

/*						Setters								*/
void	User::setCommandEnd(bool b) {

	_commandEnd = b;
}

void	User::setNickname(std::string nickname) {

	_nick = nickname;
}

/************************************************************/
/*					Member functions						*/
/************************************************************/
void	User::addToBuf(char* buf) {

	_commandBuf += buf;
	if ((_commandBuf.find("\r\n", 0) != std::string::npos))
	{
		std::cout << "complete buf: " << _commandBuf;
		_commandEnd = true;
	}
}

void	User::execCommand(std::string commandLine) {

	std::string			commandName;
	std::stringstream	lineStream(commandLine);

	lineStream >> commandName;
	std::cout << "lS = " << lineStream.str() << std::endl << "commandName = " << commandName << std::endl;;

	Command currentCommand(commandName);

	currentCommand.launchCommand(lineStream, *this);
	lineStream.clear();
}

void	User::handleCommand(char* buffer) {

	std::cout << "Buf receives" << ": " << buffer << std::endl;
	addToBuf(buffer);
	if (getCommandEnd())
	{
		execCommand(getCommandBuf());
		setCommandEnd(false);
		_commandBuf.clear();
	}
}