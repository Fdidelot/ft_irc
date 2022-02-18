/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemoreau <bemoreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 15:58:08 by fdidelot          #+#    #+#             */
/*   Updated: 2022/02/18 11:15:30 by bemoreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include <sys/types.h> // getaddrinfo
# include <sys/socket.h> // getaddrinfo
# include <netdb.h> // getaddrinfo

# include <stdexcept> // exception
# include <iostream> // cerr,cout,endl
# include <cstdlib> // exit
# include <cstring> // bzero
# include <unistd.h> // close
# include <stdio.h> // perror
# include <sstream> // flefleche
# include <map> // map
# include <ctime> // time()

// getaddrinfo, bind, select, accept
# include <stdlib.h>
# include <string>
# include <unistd.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <netdb.h>
//

# define SERV_NAME "Cthulhu"
# define SERV_VERSION "0.1"
# define CREATION_DATE "Today"

# define MOTD "Welcome to our ft_irc server !"

# define OPERNAME "ircserver"
# define OPERPASS "karmineCorp"

# define SUCCESS 0
# define SUCCESS_ADD 1
# define FAILURE_ADD 0
# define FAILURE_GETADDRINFO 1
# define FAILURE_BINDING 2
# define FAILURE_LISTEN 3
# define FAILURE_SELECT 4
# define ERROR -1
# define BACKLOG 10   // how many pending connections queue will hold

# include "Command.hpp"
# include "User.hpp"
# include "Channel.hpp"

class User;
class Channel;

class Server {

	public:
		typedef std::map<std::string, Channel> Channel_map;
		typedef std::map<std::string, Channel>::iterator Channel_map_it;

	public:

		Server(void);
		~Server(void);

		void	launchServer(char* port, char* password);
		void	initHints(void);
		void	initAi(char* port);
		void	bindToFirst(void);
		void	tryListen(void);
		void	runSelect(void);
		void	newConnection(void);
		void	endConnection(int currentSocket);
		void*	getInAddr(struct sockaddr* sa);
		void	execCommand(std::string commandLine);
		User*	getUser(std::string name);
		Channel*	getChannel(std::string name);
		std::string		getPassword();

		int		getCurrentClient(void) const;

		void	sendToEveryone(int currentSocket); // ça va s'en aller ça, fin sans doute
		void	createChannel(std::string name);
		void	eraseChannel(std::string name)
		{
			_channels.erase(name);
		}

		class badArgumentsCountException : public std::exception {

			public:

				const char* what() const throw() {

					return ("Wrong number of arguments\n"
								"Usage : ./ircserv <port> <password>");
				}
		};

	private:

		fd_set				_masterFds;			// master file descriptor list
		fd_set				_readFds;			// temporary file descriptor list for select(2)
		struct addrinfo		_hints; 			// hint struct for getaddrinfo to set _ai
		struct addrinfo		*_ai;				// list of struct given by getaddrinfo use for binding
		int					_listener;			// listening socket descriptor
		int					_fdMax;				// maximum file descriptor number
		int					_nbytes;			// number of bytes read
		std::string			_password; 			// password defined by the server
		char				_buf[256];			// buffer for client data
		int					_currentClient; 	// store the current client fd
		std::map<int, User>	_users; 			// list of users associate with fd
		Channel_map			_channels;			// list of channels associate with names
};

#endif
