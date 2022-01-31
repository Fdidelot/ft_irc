/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdidelot <fdidelot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 15:58:08 by fdidelot          #+#    #+#             */
/*   Updated: 2022/01/31 20:48:42 by fdidelot         ###   ########.fr       */
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

// getaddrinfo, bind, select, accept
#include <stdlib.h>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
//

# define SUCCESS 0
# define FAILURE_GETADDRINFO 1
# define FAILURE_BINDING 2
# define FAILURE_LISTEN 3
# define ERROR -1
# define BACKLOG 10   // how many pending connections queue will hold

//////////////////////////////// to remove
int	launchServer(char* port);
///////////////////////////////////////

class Server {

	public:

		Server(void);
		~Server(void);

		void	launchServer(char* port, char* password);
		void	initHints(void);
		void	initAi(char* port);
		void	bindToFirst(void);
		void	tryListen(void);

		// fd_set&	getMasterFds(void);
		// fd_set&	getReadFds(void);

		class badArgumentsCountException : public std::exception {

			public:

				const char* what() const throw() {

					return ("Wrong number of arguments\n"
								"Usage : ./ircserv <port> <password>");
				}
		};

	private:

		fd_set					_masterFds;	// master file descriptor list
		fd_set					_readFds;	// temporary file descriptor list for select()
		struct addrinfo			_hints; 	// hint struct for getaddrinfo to set _ai
		struct addrinfo			*_ai; 		// list of struct give by getaddrinfo use for binding
		int						_listener;	// listening socket descriptor
		// int						_fdmax;		// maximum file descriptor number
		// int						_newfd;        // newly accept()ed socket descriptor
		// struct sockaddr_storage	_remoteaddr; // client address
		// socklen_t				_addrlen;
		// char					_buf[256];    // buffer for client data
		// int						_nbytes;
		// char					_remoteIP[INET6_ADDRSTRLEN];
		// int 					_yes=1;        // for setsockopt() SO_REUSEADDR, below
		// int 					_i, _j;

};

#endif