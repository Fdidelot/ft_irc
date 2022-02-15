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

# define DEFAULT_NICKNAME " * "

class Server;

typedef struct s_mode
{
	bool	a;
	bool	i;
	bool	w;
	bool	r;
	bool	o;
	bool	O;
	bool	s;
}	t_mode;

class User
{
	public:

		User(void);
		User(int fd, Server* server);
		~User(void);

		bool	addToBuf(void);

		bool		getCommandEnd(void) const;
		int			getFd(void) const;
		std::string	getNick(void) const;
		std::string	getCommandBuf(void) const;
		bool		getUserOrNickCmd(void) const;
		bool		getMode(char m) const;
		std::string	getModes(void) const;
		char		getErrModeChar(void) const;
		Server&		getServer(void) const;

		void	setCommandEnd(bool b);
		void	setNickname(std::string nickname);
		void	setUserOrNickCmd(bool b);
		void	setMode(bool onOff, const char* modes);
		void	setErrModeChar(char c);

		void	handleCommand(char* buffer);
		void	execCommand(std::string commandLine);

	private:

		bool			_userOrNickCmd;
		bool			_commandEnd; // true means commandBuf is ready to be exec
		std::string		_commandBuf; // store the command
		std::string		_totalBuf; // store the command
		int				_fd; // socket id link to this user
		std::string		_nick; // nickname of the user
		t_mode			_mode; // user actual mode
		Server*			_server;
		char			_errModeChar;

};

#endif