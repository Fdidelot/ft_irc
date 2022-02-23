/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 15:05:02 by psemsari          #+#    #+#             */
/*   Updated: 2022/02/23 15:54:10 by psemsari         ###   ########.fr       */
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
		users_list&	getList()
		{
			return (_users);
		}
		std::string getTopic()
		{
			return (_topic);
		}
		void setName(std::string name);
		void addToChannel(User *user);
		void addToInvite(User *user);
		void addOpToChannel(User *user);
		void removeFromChannel(User *user);
		void sendToChannel(std::string str, Command &command, int notsend);

	private:
		int	mode_k;
		std::string _name;
		std::string _topic;
		std::string _pass;
		users_list	_users;
		users_list	_opers;
		users_list	_invite;
};

#endif
