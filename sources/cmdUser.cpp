/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdUser.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 17:25:56 by psemsari          #+#    #+#             */
/*   Updated: 2022/02/15 17:26:11 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

void	Command::_user(std::stringstream& completeCommand, User& user) {

	(void)completeCommand; (void)user;
	if (user.getUserOrNickCmd())
		sendStartMsgs(user);
	user.setUserOrNickCmd(true);
}
