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

# include "User.hpp"
# define NB_COMMAND 4

class User;

class Command
{
	public:

		Command(std::string commandName = "Unknown");
		~Command(void);

		void	launchCommand(std::stringstream& completeCommand, User& user);

	private:

		std::string	_type;
		void		_pass(std::stringstream& completeCommand, User& user);
		void		_nick(std::stringstream& completeCommand, User& user);
		void		_user(std::stringstream& completeCommand, User& user);
		void		_cap(std::stringstream& completeCommand, User& user);
};

#endif
