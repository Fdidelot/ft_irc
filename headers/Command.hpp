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
# define NB_COMMAND 6
# define EOT_CODE 4
# define SEND_OPT 0

# define RPL_MESSAGE(servName, number, nick) (":" + servName + " " + number + " " + nick + " ")
# define RPL_WELCOME(nick) (":Welcome to the Internet Relay Network " + nick)
# define RPL_YOURHOST(servName, servVersion) (":Your host is " + servName + ", running version " + servVersion)
# define RPL_CREATED(date) (":This server was created " + date)
# define RPL_MYINFO(servName, servVersion) (":" + servName + " " + servVersion + " user_mode, channel modes")

// enum e
// {
// 	RPL_WELCOME = 1
// };

class User;

class Command
{
	public:

		Command(std::string commandName = "Unknown");
		~Command(void);

		void	launchCommand(std::stringstream& completeCommand, User& user);
		void	sendCommand(User& user, int msgId) const;
		void	sendStartMsgs(User& user) const;

	private:

		std::string	_type;
		void		_pass(std::stringstream& completeCommand, User& user);
		void		_nick(std::stringstream& completeCommand, User& user);
		void		_user(std::stringstream& completeCommand, User& user);
		void		_cap(std::stringstream& completeCommand, User& user);
		void		_mode(std::stringstream& completeCommand, User& user);
		void		_join(std::stringstream& completeCommand, User& user);
};

#endif
