/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 15:57:10 by fdidelot          #+#    #+#             */
/*   Updated: 2022/02/15 17:40:55 by psemsari         ###   ########.fr       */
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
int	Server::getCurrentClient(void) const {

	return (_currentClient);
}

User*	Server::getUser(std::string name)
{
	std::map<int, User>::iterator it = _users.begin();
	std::map<int, User>::iterator ite = _users.end();

	for (; it->first != ite->first; it++)
	{
		if (it->second.getNick() == name)
			return (&it->second);
	}
	return (NULL);
}

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

	struct timeval timeout;

	timeout.tv_sec = 1;
	timeout.tv_usec = 0;
	if (select(_fdMax + 1, &_readFds, NULL, NULL, &timeout) == -1) {
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
		_users[newFd] = User(newFd, this);
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
		for (_currentClient = 0; _currentClient <= _fdMax; _currentClient++)
		{
			if (FD_ISSET(_currentClient, &_readFds))
			{
				if (_currentClient == _listener)
					newConnection();
				else
				{
					bzero(&_buf, sizeof(_buf));
					_nbytes = recv(_currentClient, _buf, sizeof(_buf), 0);
					if (_nbytes < 1)
						endConnection(_currentClient);
					else
					{

						_users[_currentClient].handleCommand(_buf);
						// sendToEveryone(_currentClient);
					}
				}
			}
		}
	}
}
