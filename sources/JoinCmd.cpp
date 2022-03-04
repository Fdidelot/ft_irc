/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdJoin.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdidelot <fdidelot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 20:25:42 by fdidelot          #+#    #+#             */
/*   Updated: 2022/03/04 21:41:46 by fdidelot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"
#include <cstring>

void	Command::_join(std::stringstream& completeCommand, User& user) {

	std::list<std::string> toJoin, pass;
	std::stringstream stream;
	std::string str, word;

	completeCommand >> str;
	stream.str(str);
	while (!stream.eof()) {
		std::getline(stream, word, ',');
		toJoin.push_back(word);
	}
	if (!completeCommand.eof())
	{
		completeCommand >> str;
		stream.str(str);
		stream.seekg(0);
		while (!stream.eof()) {
			std::getline(stream, word, ',');
			pass.push_back(word);
		}
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
		if (pass.empty() || !channel->addToChannel(&user, pass.front()))
		{
			user.addChannel(channel);
			channel->addToChannel(&user);
			channel->sendToChannel(":" + user.getNickHost() +" JOIN " + toJoin.front() + "\r\n", *this, user.getFd());
			sendCommand(user, PONG, ":" + user.getNickHost() +" JOIN " + toJoin.front() + "\r\n");
			sendCommand(user, RPLCODE_NAMREPLY, "= " + RPL_NAMREPLY(toJoin.front(), channel->usersFormat()));
			sendCommand(user, RPLCODE_ENDOFNAMES, RPL_ENDOFNAMES(toJoin.front()));
		}
		else
			sendCommand(user, ERRCODE_BADCHANNELKEY, ERR_BADCHANNELKEY(toJoin.front()));
		if (!pass.empty())
			pass.pop_front();
		toJoin.pop_front();
	}
}
