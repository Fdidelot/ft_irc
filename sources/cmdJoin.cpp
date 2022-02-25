/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdJoin.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 17:23:09 by psemsari          #+#    #+#             */
/*   Updated: 2022/02/25 15:54:32 by psemsari         ###   ########.fr       */
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
	std::cout << "YOOYOYOYOYOYOYO" << std::endl;
	completeCommand >> str;
	stream << str;
	while (std::getline(stream, word, ','))
	{
		toJoin.push_back(word);
		std::cout << "word = " << word << std::endl;
	}
	str.clear();
	completeCommand >> str;
	stream.clear();
	stream << str;
	while (std::getline(stream, word, ','))
	{
		pass.push_back(word);
		std::cout << "word = " << word << std::endl;
	}


	// while (completeCommand >> toJoin)
	// {
	// 	std::cout << "OUTPUT toJoin = " << toJoin << std::endl;
	// 	Channel* channel = user.getServer().getChannel(toJoin);
	// 	if (channel == NULL)
	// 	{
	// 		user.getServer().createChannel(toJoin);
	// 		channel = user.getServer().getChannel(toJoin);
	// 		channel->setName(toJoin);
	// 	}
	// 	channel->addToChannel(&user);//euheuheueh
	// 	user.addChannel(channel);
	// }
	// sendCommand(user, PONG, completeCommand.str() + "\r\n");
}
