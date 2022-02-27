/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdJoin.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 17:23:09 by psemsari          #+#    #+#             */
/*   Updated: 2022/02/27 23:52:23 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

void	Command::_join(std::stringstream& completeCommand, User& user) {

	std::list<std::string> toJoin;
	std::list<std::string> pass;
	std::stringstream stream;
	std::string str;
	std::string word;

	(void)user;
	completeCommand >> str;
	stream << str;
	std::cout << stream.str() << std::endl;
	while (std::getline(stream, word, ','))
		toJoin.push_back(word);
	str.clear();
	completeCommand >> str;
	std::cout << stream.str() << std::endl;
	stream.clear();
	stream << str;
	if (!stream.eof())
	{
		while (std::getline(stream, word, ','))
			pass.push_back(word);
	}

	while (!toJoin.empty())
	{
		Channel* channel = user.getServer().getChannel(toJoin.front());
		if (channel == NULL)
		{
			user.getServer().createChannel(toJoin.front());
			channel = user.getServer().getChannel(toJoin.front());
			channel->setName(toJoin.front());
		}
		if (pass.empty() || !channel->addToChannel(&user, pass.front()))//revoir
		{
			user.addChannel(channel);
			sendCommand(user, PONG, "JOIN " + toJoin.front() + "\r\n");
			pass.pop_front();
		}
		else
			sendCommand(user, ERRCODE_BADCHANNELKEY, ERR_BADCHANNELKEY(toJoin.front()));
		toJoin.pop_front();
	}
}
