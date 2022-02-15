/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 15:09:45 by psemsari          #+#    #+#             */
/*   Updated: 2022/02/15 15:58:32 by psemsari         ###   ########.fr       */
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

void Channel::addToChannel(User *user)
{
	_users.push_back(user);
}

void Channel::removeFromChannel(User *user)
{
	_users.remove(user);
}

void Channel::sendToChannel(std::string str)
{
	(void)str;
	users_list::iterator it;
	while (*it)
	{
		//send((*it)->getFd(), str.c_str(), str.size(), NULL); //PRIVMSG
		it++;
	}
}

void Channel::addOpToChannel(User *user)
{
	_opers.push_back(user);
}
