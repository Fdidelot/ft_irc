/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 15:05:02 by psemsari          #+#    #+#             */
/*   Updated: 2022/02/22 18:08:30 by psemsari         ###   ########.fr       */
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
		void setName(std::string name);
		void addToChannel(User *user);
		void addOpToChannel(User *user);
		void removeFromChannel(User *user);
		void sendToChannel(std::string str, Command &command, int notsend);

	private:
		std::string _name;
		std::string _topic;
		users_list	_users;
		users_list	_opers;
};

#endif
