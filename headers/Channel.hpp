/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdidelot <fdidelot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 20:35:06 by fdidelot          #+#    #+#             */
/*   Updated: 2022/03/04 20:35:07 by fdidelot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "User.hpp"
# include "Command.hpp"
# include <list>

class User;

class Command;

class Channel
{
	public:
		typedef std::list<User *> users_list; // à refaire avec des references

	public:
		Channel(){}
		Channel(std::string name);
		~Channel();
		std::string getName();
		users_list&	getList();
		std::string getTopic();
		bool getModeI();
		bool getModeK();
		void setName(std::string name);
		void setModeI(bool mode);
		void setModeK(bool mode);
		void addToChannel(User *user);
		bool addToChannel(User *user, std::string pass);
		void addToInvite(User *user);
		void addOpToChannel(User *user);
		void removeFromChannel(User *user);
		void sendToChannel(std::string str, Command &command, int notsend);
		std::string usersFormat();

	private:
		bool		_mode_i;
		bool		_mode_k;
		std::string	_name;
		std::string	_topic;
		std::string	_pass;
		users_list	_users;
		users_list	_opers;
		users_list	_invite;
};

#endif
