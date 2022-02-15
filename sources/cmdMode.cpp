/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdMode.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 17:23:40 by psemsari          #+#    #+#             */
/*   Updated: 2022/02/15 17:23:52 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

void	Command::_mode(std::stringstream& completeCommand, User& user) {

	std::string	word;
	int			i = 0;
	while (completeCommand >> word)
		i++;
	user.setMode((*word.c_str() == '-' ? false : true), word.c_str());
	sendCommand(user, MODE);
}