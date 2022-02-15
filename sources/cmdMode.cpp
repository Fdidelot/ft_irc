/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdMode.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdidelot <fdidelot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 17:23:40 by psemsari          #+#    #+#             */
/*   Updated: 2022/02/15 19:01:01 by fdidelot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

void	Command::_mode(std::stringstream& completeCommand, User& user) {

	std::string	word;
	int			i = 0;
	while (completeCommand >> word)
		i++;
	user.setMode((*word.c_str() == '-' ? false : true), word.c_str());
	sendCommand(user, RPLCODE_UMODEIS, RPL_UMODEIS(user.getModes()));
}
