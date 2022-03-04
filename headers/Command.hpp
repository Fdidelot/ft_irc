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
# define NB_COMMAND 15 //add if command
# define EOT_CODE 4

# include "err.hpp"
# include "rpl.hpp"

class User;

class Command
{
	public:

		Command(std::string commandName = "Unknown");
		~Command(void);

		void    printUserData(User& user, User *target);
		bool	findByUsername(User& user, std::string name, bool oper);
		void    listUsersFromChannel(User usr, std::map<int, User> users, std::string chan, bool oper);
		bool	findNicknameOccurence(User& user, std::map<int, User> users, bool oper, std::string mask);
		void    showAllUsers(User usr, std::map<int, User> users, bool oper);
		void	launchCommand(std::stringstream& completeCommand, User& user);
		void	sendCommand(User& user, int msgId, std::string toSend) const;
		void	sendDirect(User& user, int msgId, std::string toSend) const;
		void	sendStartMsgs(User& user) const;

	private:

		std::string	_type;
		void		_pass(std::stringstream& completeCommand, User& user);
		void		_nick(std::stringstream& completeCommand, User& user);
		void		_user(std::stringstream& completeCommand, User& user);
		void		_cap(std::stringstream& completeCommand, User& user);
		void		_mode(std::stringstream& completeCommand, User& user);
		void		_join(std::stringstream& completeCommand, User& user);
		void		_ping(std::stringstream& completeCommand, User& user);
		void		_privmsg(std::stringstream& completeCommand, User& user);
		void		_part(std::stringstream& completeCommand, User& user);
		void		_quit(std::stringstream& completeCommand, User& user);
		void		_oper(std::stringstream& completeCommand, User& user);
		void		_motd(std::stringstream& completeCommand, User& user);
		void		_kill(std::stringstream& completeCommand, User& user);
		void		_whois(std::stringstream& completeCommand, User& user);
		void		_notice(std::stringstream& completeCommand, User& user);
};

#endif
