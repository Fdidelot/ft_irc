/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdidelot <fdidelot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 21:44:55 by fdidelot          #+#    #+#             */
/*   Updated: 2021/12/16 18:10:47 by fdidelot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USER_HPP
# define USER_HPP

# include <iostream>

# include "Server.hpp"

class User
{
	public:

		User(void);
		User(int fd);
		~User(void);

		void	addToBuf(char* buf);

		bool		getCommandEnd(void) const;
		int			getFd(void) const;
		std::string	getCommandBuf(void) const;

		void	setCommandEnd(bool b);
		void	setNickname(std::string nickname);

		void	handleCommand(char* buffer);
		void	execCommand(std::string commandLine);

	private:

		bool			_commandEnd; // true mean commandBuf is ready to be exec
		std::string		_commandBuf; // store the command
		int				_fd; // socket id link to this user
		std::string		_nick; // nickname of the user
	
};

#endif
