/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 15:05:02 by psemsari          #+#    #+#             */
/*   Updated: 2022/02/14 17:36:45 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "User.hpp"
# include <list>

class User;

class Channel
{
	public:
		typedef std::list<User *> users_list;

	public:
		Channel(std::string name);
		~Channel();
		std::string getName();
		void addToChannel(User *user);
		void addOpToChannel(User *user);
		void removeFromChannel(User *user);
		void sendToChannel(std::string str);

	private:
		std::string _name;
		users_list	_users;
		users_list	_opers;
};

#endif
