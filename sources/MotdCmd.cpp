/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdMotd.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdidelot <fdidelot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 19:02:45 by fdidelot          #+#    #+#             */
/*   Updated: 2022/03/04 20:26:15 by fdidelot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

void	Command::_motd(std::stringstream& completeCommand, User& user) {

    (void)completeCommand;
    std::string msg = MOTD;
    if (msg.empty() == true)
    {
        sendCommand(user, 422, ERR_NOMOTD());
        return;
    }
    std::string name = static_cast<std::string>(SERV_NAME);
    sendCommand(user, 375, RPL_MOTDSTART(name));
    sendCommand(user, 372, RPL_MOTD(msg));
    sendCommand(user, 376, RPL_ENDOFMOTD());
}
