/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 15:09:45 by psemsari          #+#    #+#             */
/*   Updated: 2022/02/21 16:01:12 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

Channel::Channel(std::string name) : _name(name)
{
}

Channel::~Channel()
{
}

std::string Channel::getName()
{
	return (_name);
}

void Channel::setName(std::string name)
{
	_name = name;
}

void Channel::addToChannel(User *user)
{
	_users.push_back(user);
}

void Channel::removeFromChannel(User *user)
{
	_users.remove(user);
}

void Channel::sendToChannel(std::string str, Command &command, int notsend)
{
	users_list::iterator it = _users.begin();
	users_list::iterator ite = _users.end();
	for (; it != ite; it++)
		if ((*it)->getFd() != notsend)
			command.sendDirect(**it, PONG, str);
}

void Channel::addOpToChannel(User *user)
{
	_opers.push_back(user);
}
