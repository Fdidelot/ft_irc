/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdidelot <fdidelot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 21:44:55 by fdidelot          #+#    #+#             */
/*   Updated: 2021/12/16 18:10:47 by fdidelot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_HPP
# define COMMAND_HPP

# include "Server.hpp"
# define NB_COMMAND 4

class Command
{
	public:

		Command(std::string commandName = "Unknown");
		~Command(void);

		void	launchCommand(std::stringstream& completeCommand);

	private:

		std::string	_type;
		void		_pass(std::stringstream& completeCommand);
		void		_nick(std::stringstream& completeCommand);
		void		_user(std::stringstream& completeCommand);

};

#endif
