/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdidelot <fdidelot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 15:57:10 by fdidelot          #+#    #+#             */
/*   Updated: 2022/01/27 17:43:17 by fdidelot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

int	launchServer(char* port)
{
	struct addrinfo	hints, *result, *resultOrigin;
	int	sockFd, ret;

	bzero(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE; // assign the address of local host to the socket struct
	
	ret = getaddrinfo(NULL, port, &hints, &result);
	if (ret != 0)
	{
		std::cerr << "getaddrinfo: " << gai_strerror(ret) << std::endl;
		return (FAILURE);
	}
	// int i = 0;
	for (resultOrigin = result; result != NULL; result = result->ai_next)
	{
		sockFd = socket(result->ai_family, result->ai_socktype,
				result->ai_protocol);
		if (sockFd == ERROR)
		{
			perror("server: socket");
			continue;
		}
		// if (setsockopt() == ERROR)
		// {
		// 	perror("setsockopt");
		// 	exit (ERROR);
		// }
		if (bind(sockFd, result->ai_addr, result->ai_addrlen) == ERROR)
		{
			close (sockFd);
			perror("server: bind");
			continue;
		}
		// AFFICHAGE DOUTEUX
		// std::cout << result << std::endl;
		// std::cout << "num " << i++ << std::endl;
		// std::cout << "ai_addr:" << result->ai_addr << std::endl;
		// std::cout << "ai_addrlen:" << result->ai_addrlen << std::endl;
		// std::cout << "ai_family:" << result->ai_family << std::endl;
		// std::cout << "ai_flags:" << result->ai_flags << std::endl;
		// std::cout << "ai_next:" << result->ai_next << std::endl;
		// std::cout << "ai_protocol:" << result->ai_protocol << std::endl;
		// std::cout << "ai_socktype:" << result->ai_socktype << std::endl;
		// std::cerr << "ai_canonname:" << result->ai_canonname << std::endl;
		// std::cout << std::endl;
		break ;
	}
	freeaddrinfo(resultOrigin);
	if (result == NULL)
	{
		std::cerr << "server: failed to bind." << std::endl;
		exit(ERROR);
	}
	if (listen(sockFd, BACKLOG))
	{
		perror("listen");
		exit(ERROR);
	}
	while (1)
	{
		
	}
	//paul/select
		//accept
	return (SUCCESS);
}