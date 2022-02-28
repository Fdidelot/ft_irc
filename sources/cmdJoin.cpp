/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdJoin.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 17:23:09 by psemsari          #+#    #+#             */
/*   Updated: 2022/02/28 13:32:54 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"
#include <cstring>

void	Command::_join(std::stringstream& completeCommand, User& user) {

	std::list<std::string> toJoin;
	std::list<std::string> pass;
	std::stringstream stream;
	std::string str;
	std::string word;

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
		if (pass.empty() || !channel->addToChannel(&user, pass.front()))//revoir
		{
			user.addChannel(channel);
			channel->addToChannel(&user);
			channel->sendToChannel("JOIN " + toJoin.front() + "\r\n", *this, 0);
		}
		else
			sendCommand(user, ERRCODE_BADCHANNELKEY, ERR_BADCHANNELKEY(toJoin.front()));
		if (!pass.empty())
			pass.pop_front();
		toJoin.pop_front();
	}
}
