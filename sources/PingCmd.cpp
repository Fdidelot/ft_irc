/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdPing.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdidelot <fdidelot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 20:27:39 by fdidelot          #+#    #+#             */
/*   Updated: 2022/03/04 20:27:40 by fdidelot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

void	Command::_ping(std::stringstream& completeCommand, User& user) {

	std::string servName = static_cast<std::string>(SERV_NAME);

	(void)completeCommand;
	sendCommand(user, PONG, PONG_MSG(servName));
}
