/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdNick.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdidelot <fdidelot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 17:24:04 by psemsari          #+#    #+#             */
/*   Updated: 2022/02/16 18:48:28 by fdidelot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

void	Command::_nick(std::stringstream& completeCommand, User& user) {

	std::string nickname;

	completeCommand >> nickname;
	user.setNickname(nickname);
	if (user.getUserOrNickCmd())
		sendStartMsgs(user);
	user.setUserOrNickCmd(true);
}
