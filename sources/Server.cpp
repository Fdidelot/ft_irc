/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdidelot <fdidelot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 15:57:10 by fdidelot          #+#    #+#             */
/*   Updated: 2022/01/31 20:50:59 by fdidelot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

// int	launchServer(char* port)
// {
// 	struct addrinfo	hints, *result, *resultOrigin;
// 	struct sockaddr_storage storageAddr;
// 	int	sockFd, newFd,ret;
// 	socklen_t	sockSize;

// 	bzero(&hints, sizeof(hints));
// 	hints.ai_family = AF_UNSPEC;
// 	hints.ai_socktype = SOCK_STREAM;
// 	hints.ai_flags = AI_PASSIVE; // assign the address of local host to the socket struct
	
// 	ret = getaddrinfo(NULL, port, &hints, &result);
// 	if (ret != 0)
// 	{
// 		std::cerr << "getaddrinfo: " << gai_strerror(ret) << std::endl;
// 		return (FAILURE);
// 	}
// 	// int i = 0;
// 	for (resultOrigin = result; result != NULL; result = result->ai_next)
// 	{
// 		sockFd = socket(result->ai_family, result->ai_socktype,
// 				result->ai_protocol);
// 		if (sockFd == ERROR)
// 		{
// 			perror("server: socket");
// 			continue;
// 		}
// 		// if (setsockopt() == ERROR)
// 		// {
// 		// 	perror("setsockopt");
// 		// 	exit (ERROR);
// 		// }
// 		if (bind(sockFd, result->ai_addr, result->ai_addrlen) == ERROR)
// 		{
// 			close (sockFd);
// 			perror("server: bind");
// 			continue;
// 		}
// 		// AFFICHAGE DOUTEUX
// 		// std::cout << result << std::endl;
// 		// std::cout << "num " << i++ << std::endl;
// 		// std::cout << "ai_addr:" << result->ai_addr << std::endl;
// 		// std::cout << "ai_addrlen:" << result->ai_addrlen << std::endl;
// 		// std::cout << "ai_family:" << result->ai_family << std::endl;
// 		// std::cout << "ai_flags:" << result->ai_flags << std::endl;
// 		// std::cout << "ai_next:" << result->ai_next << std::endl;
// 		// std::cout << "ai_protocol:" << result->ai_protocol << std::endl;
// 		// std::cout << "ai_socktype:" << result->ai_socktype << std::endl;
// 		// std::cerr << "ai_canonname:" << result->ai_canonname << std::endl;
// 		// std::cout << std::endl;
// 		break ;
// 	}
// 	freeaddrinfo(resultOrigin);
// 	if (result == NULL)
// 	{
// 		std::cerr << "server: failed to bind." << std::endl;
// 		exit(ERROR);
// 	}
// 	if (listen(sockFd, BACKLOG))
// 	{
// 		perror("listen");
// 		exit(ERROR);
// 	}
// 	while (1)
// 	{
// 		sockSize = sizeof(storageAddr);
// 		accept()
// 	}
// 	return (SUCCESS);
// }

/************************************************************/
/*					Constructor/Destructor					*/
/************************************************************/
Server::Server(void) {

	FD_ZERO(&_masterFds);
	FD_ZERO(&_readFds);
	initHints();
	return ;
}

Server::~Server(void) {

	return ;
}

/************************************************************/
/*					Getters/Setters							*/
/************************************************************/
/*						Getters								*/
// fd_set&	Server::getMasterFds(void) {

// 	return (_masterFds);
// }

// fd_set&	Server::getReadFds(void) {

// 	return (_readFds);
// }

/*						Setters								*/

/************************************************************/
/*					Members functions						*/
/************************************************************/
void	Server::initHints(void) {

	bzero(&_hints, sizeof(_hints));
	_hints.ai_family = AF_UNSPEC;
	_hints.ai_socktype = SOCK_STREAM;
	_hints.ai_flags = AI_PASSIVE;
}

void	Server::initAi(char* port) {

	int	retGetAddrinfo;

	retGetAddrinfo = getaddrinfo(NULL, port, &_hints, &_ai);
	if (retGetAddrinfo != SUCCESS)
	{
		std::cerr << "ircserv: " << gai_strerror(retGetAddrinfo) << std::endl;
		exit (FAILURE_GETADDRINFO);
	}	
}

void	Server::bindToFirst(void) {

	struct addrinfo	*_p;
	int				yes = 1;

	for(_p = _ai; _p != NULL; _p = _p->ai_next) {
		_listener = socket(_p->ai_family, _p->ai_socktype, _p->ai_protocol);
		if (_listener < 0) { 
			continue;
		}
		setsockopt(_listener, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
		if (bind(_listener, _p->ai_addr, _p->ai_addrlen) < 0) {
			close(_listener);
			continue;
		}
		break;
	}
	if (_p == NULL) {
		fprintf(stderr, "ircserv: failed to bind\n");
		exit(FAILURE_BINDING);
	}
	freeaddrinfo(_ai);
}

void	Server::tryListen(void) {

	if (listen(_listener, BACKLOG) == -1)
	{
		perror("listen");
		exit(FAILURE_LISTEN);
	}
	FD_SET(_listener, &_masterFds);
}

void	Server::launchServer(char* port, char* password)
{
	(void)password; // WARNING

	initAi(port);
	bindToFirst();
	tryListen();
}

// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
	if (sa->sa_family == AF_INET) {
		return &(((struct sockaddr_in*)sa)->sin_addr);
	}
	return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int launchServer(char *port)
{
	fd_set master;    // master file descriptor list
	fd_set read_fds;  // temp file descriptor list for select()
	int fdmax;        // maximum file descriptor number

	int listener;     // listening socket descriptor
	int newfd;        // newly accept()ed socket descriptor
	struct sockaddr_storage remoteaddr; // client address
	socklen_t addrlen;

	char buf[256];    // buffer for client data
	int nbytes;

	char remoteIP[INET6_ADDRSTRLEN];

	int yes=1;        // for setsockopt() SO_REUSEADDR, below
	int i, j, rv;

	struct addrinfo hints, *ai, *p;

	FD_ZERO(&master);    // clear the master and temp sets
	FD_ZERO(&read_fds);

	// get us a socket and bind it
	bzero(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;
	if ((rv = getaddrinfo(NULL, port, &hints, &ai)) != 0) {
		fprintf(stderr, "ircserv: %s\n", gai_strerror(rv));
		exit(1);
	}
	
	for(p = ai; p != NULL; p = p->ai_next) {
		listener = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
		if (listener < 0) { 
			continue;
		}
		
		// lose the pesky "address already in use" error message
		setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));

		if (bind(listener, p->ai_addr, p->ai_addrlen) < 0) {
			close(listener);
			continue;
		}

		break;
	}

	// if we got here, it means we didn't get bound
	if (p == NULL) {
		fprintf(stderr, "ircserv: failed to bind\n");
		exit(2);
	}

	freeaddrinfo(ai); // all done with this

	// listen
	if (listen(listener, 10) == -1) {
		perror("listen");
		exit(3);
	}

	// add the listener to the master set
	FD_SET(listener, &master);


//////////////////////////////////////////////////////////////////
	// keep track of the biggest file descriptor
	fdmax = listener; // so far, it's this one

	// main loop
	for(;;) {
		read_fds = master; // copy it
		if (select(fdmax+1, &read_fds, NULL, NULL, NULL) == -1) {
			perror("select");
			exit(4);
		}

		// run through the existing connections looking for data to read
		for(i = 0; i <= fdmax; i++) {
			if (FD_ISSET(i, &read_fds)) { // we got one!!
				if (i == listener) {
					// handle new connections
					addrlen = sizeof remoteaddr;
					newfd = accept(listener,
						(struct sockaddr *)&remoteaddr,
						&addrlen);

					if (newfd == -1) {
						perror("accept");
					} else {
						FD_SET(newfd, &master); // add to master set
						if (newfd > fdmax) {    // keep track of the max
							fdmax = newfd;
						}
						printf("ircserv: new connection from %s on "
							"socket %d\n",
							inet_ntop(remoteaddr.ss_family,
								get_in_addr((struct sockaddr*)&remoteaddr),
								remoteIP, INET6_ADDRSTRLEN),
							newfd);
					}
				} else {
					// handle data from a client
					if ((nbytes = recv(i, buf, sizeof buf, 0)) <= 0) {
						// got error or connection closed by client
						if (nbytes == 0) {
							// connection closed
							printf("ircserv: socket %d hung up\n", i);
						} else {
							perror("recv");
						}
						close(i); // bye!
						FD_CLR(i, &master); // remove from master set
					} else {
						std::cout << "buf: " << buf << std::endl;
						// we got some data from a client
						for(j = 0; j <= fdmax; j++) {
							// send to everyone!
							if (FD_ISSET(j, &master)) {
								// except the listener and ourselves
								if (j != listener && j != i) {
									if (send(j, buf, nbytes, 0) == -1) {
										perror("send");
									}
								}
							}
						}
					}
				} // END handle data from client
			} // END got new incoming connection
		} // END looping through file descriptors
	} // END for(;;)--and you thought it would never end!
	
	return 0;
}