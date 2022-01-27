/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdidelot <fdidelot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 15:58:08 by fdidelot          #+#    #+#             */
/*   Updated: 2022/01/27 17:43:41 by fdidelot         ###   ########.fr       */
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

# define FAILURE 0
# define SUCCESS 1
# define ERROR -1
# define BACKLOG 10   // how many pending connections queue will hold

int	launchServer(char* port);

class badArgumentsCountException : public std::exception {

	public:

		const char* what() const throw() {

			return ("Wrong number of arguments\n"
						"Usage : ./ircserv <port> <password>");
		}
};

#endif