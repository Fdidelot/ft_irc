/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdidelot <fdidelot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 20:25:21 by fdidelot          #+#    #+#             */
/*   Updated: 2022/03/04 20:25:27 by fdidelot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

Channel::Channel(std::string name) : _mode_k(false), _name(name) {

	return ;
}

Channel::~Channel() {

	return ;
}

/************************************************************/
/*					Getters/Setters							*/
/************************************************************/
/*						Getters								*/

std::string Channel::getName() {

	return (_name);
}

Channel::users_list& Channel::getList() {

	return (_users);
}

std::string Channel::getTopic() {

	return (_topic);
}

bool Channel::getModeI() {

	return (_mode_i);
}

bool Channel::getModeK() {

	return (_mode_k);
}

/*						Setters								*/

void Channel::setName(std::string name) {

	_name = name;
}

void Channel::setModeI(bool mode) {

	_mode_i = mode;
}

void Channel::setModeK(bool mode) {

	_mode_k = mode;
}

/************************************************************/
/*					Members functions						*/
/************************************************************/

void Channel::addToChannel(User *user) {

	_users.push_back(user);
}

bool Channel::addToChannel(User *user, std::string pass = "") {

	if (_mode_k == true && _pass != pass)
		return (1);
	_users.push_back(user);
	return (0);
}

void Channel::removeFromChannel(User *user) {

	_users.remove(user);
}

void Channel::sendToChannel(std::string str, Command &command, int notsend) {

	users_list::iterator it = _users.begin();
	users_list::iterator ite = _users.end();
	for (; it != ite; it++)
		if ((*it)->getFd() != notsend)
			command.sendDirect(**it, PONG, str);
}

void Channel::addOpToChannel(User *user) {

	_opers.push_back(user);
}

std::string Channel::usersFormat() {

	Channel::users_list::iterator it = _users.begin();
	Channel::users_list::iterator ite = _users.end();
	std::string ret;
	ret += (*it)->getNick();
	it++;
	for (;it != ite; it++)
	{
		ret += " " + (*it)->getNick();
	}
	return ret;
}
