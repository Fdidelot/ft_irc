/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdNick.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdidelot <fdidelot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 17:24:04 by psemsari          #+#    #+#             */
/*   Updated: 2022/02/18 19:47:25 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

void	Command::_nick(std::stringstream& completeCommand, User& user) {

	std::string nickname;

	if (user.getPassGiven() == false)
		user.setIsEnded(true);
	completeCommand >> nickname;
	std::cout << "|" << nickname << "|" << std::endl;
	if (nickname == user.getNick())
		return;
	if (user.getServer().isNicknameKilled(nickname)== true)
	{
		user.getServer().endConnection(user.getFd());
		return ;
	}
	if (user.getServer().findByNickName(user, nickname) != NULL)
	{
		sendDirect(user, 433, ERR_NICKNAMEINUSE(nickname));
		return ;
	}
	user.setNickname(nickname);
	if (user.getUserOrNickCmd())
		sendStartMsgs(user);
	user.setUserOrNickCmd(true);
}
