/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdidelot <fdidelot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 15:57:10 by fdidelot          #+#    #+#             */
/*   Updated: 2022/02/04 16:25:55 by fdidelot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

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

	for(_p = _ai; _p != NULL; _p = _p->ai_next)
	{
		_listener = socket(_p->ai_family, _p->ai_socktype, _p->ai_protocol);
		if (_listener < 0)
			continue;
		setsockopt(_listener, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
		if (bind(_listener, _p->ai_addr, _p->ai_addrlen) < 0)
		{
			close(_listener);
			continue;
		}
		break;
	}
	if (_p == NULL)
	{
		std::cerr << "ircserv: failed to bind" << std::endl;
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
}

void	Server::runSelect(void) {

	if (select(_fdMax + 1, &_readFds, NULL, NULL, NULL) == -1) {
		perror("select");
		exit(FAILURE_SELECT);
	}
}

void*	Server::getInAddr(struct sockaddr *sa) {

	if (sa->sa_family == AF_INET)
		return &(((struct sockaddr_in*)sa)->sin_addr);
	return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

void	Server::newConnection(void) {

	socklen_t				addrLen;
	struct sockaddr_storage	remoteAddr;
	int						newFd;
	char					remoteIP[INET6_ADDRSTRLEN];

	addrLen = sizeof remoteAddr;
	newFd = accept(_listener, (struct sockaddr *)&remoteAddr, &addrLen);
	if (newFd == -1)
		perror("accept");
	else
	{
		FD_SET(newFd, &_masterFds); // add to master set
		if (newFd > _fdMax)
			_fdMax = newFd;
		std::cout	<< "ircserv: new connection from "
					<< 	inet_ntop(remoteAddr.ss_family, getInAddr((struct sockaddr*)&remoteAddr),
									remoteIP, INET6_ADDRSTRLEN)
					<< " on socket "
					<< newFd
					<< std::endl;
	}
}

void	Server::endConnection(int currentSocket) {

	if (_nbytes == 0)
		std::cout << "ircserv: socket " << currentSocket << " hung up" << std::endl;
	else
		perror("recv");
	close(currentSocket);
	FD_CLR(currentSocket, &_masterFds);
}

void	Server::sendToEveryone(int currentSocket) {

	for(int j = 0; j <= _fdMax; j++)
	{
		if (FD_ISSET(j, &_masterFds))
		{
			if (j != _listener && j != currentSocket)
			{
				if (send(j, _buf, _nbytes, 0) == -1)
					perror("send");
			}
		}
	}
}

void	Server::execCommand(std::string commandName,
					std::stringstream& completeCommand) {

	Command currentCommand(commandName);

	currentCommand.launchCommand(completeCommand);
}

void	Server::fleflecheLoop(void) {

	std::string sBuf(_buf), parsedLine, tmp;
	std::stringstream stream(sBuf), lineStream;

	int i = 0;
	while (std::getline(stream, parsedLine))
	{
		lineStream.str(parsedLine);
		std::cout << "Line " << i++ << " : " <<  parsedLine << std::endl;
		lineStream >> tmp;
		execCommand(tmp, lineStream);
		lineStream.clear();
	}
}

void	Server::launchServer(char* port, char* password) {

	_password = password;
	initAi(port); // getaddrinfo
	bindToFirst(); // bind to first opened socket
	tryListen(); // try to listen on the opened port
	FD_SET(_listener, &_masterFds); // set the listener fd to the master set
	_fdMax = _listener; // set the maximum fd possible
	while (1)
	{
		_readFds = _masterFds; // copy the master to manipulate
		runSelect(); // runs select(2)
		for (int i = 0; i <= _fdMax; i++)
		{
			if (FD_ISSET(i, &_readFds))
			{
				if (i == _listener)
					newConnection();
				else
				{
					bzero(&_buf, sizeof(_buf));
					if ((_nbytes = recv(i, _buf, sizeof(_buf), 0)) < 1)
						endConnection(i);
					else
					{
						std::cout << "Buf receive from " << i << ": " << _buf << std::endl;
						fleflecheLoop();
						sendToEveryone(i);
					}
				}
			}
		}
	}
}
