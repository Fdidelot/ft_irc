/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdidelot <fdidelot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 21:36:29 by fdidelot          #+#    #+#             */
/*   Updated: 2022/03/04 21:38:36 by fdidelot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERR_HPP
# define ERR_HPP

# define ERRCODE_NOSUCHNICK			401
# define ERRCODE_NOSUCHSERVER		402
# define ERRCODE_NOSUCHCHANNEL		403
# define ERRCODE_CANNOTSENDTOCHAN	404
# define ERRCODE_TOOMANYCHANNELS	405
# define ERRCODE_WASNOSUCHNICK		406
# define ERRCODE_TOOMANYTARGETS		407
# define ERRCODE_NOORIGIN			409
# define ERRCODE_NORECIPIENT		411
# define ERRCODE_NOTEXTTOSEND		412
# define ERRCODE_NOTOPLEVEL			413
# define ERRCODE_WILDTOPLEVEL		414
# define ERRCODE_UNKNOWNCOMMAND		421
# define ERRCODE_NOMOTD				422
# define ERRCODE_NOADMININFO		423
# define ERRCODE_FILEERROR			424
# define ERRCODE_NONICKNAMEGIVEN	431
# define ERRCODE_ERRONEUSNICKNAME	432
# define ERRCODE_NICKNAMEINUSE		433
# define ERRCODE_NICKCOLLISION		436
# define ERRCODE_USERNOTINCHANNEL	441
# define ERRCODE_NOTONCHANNEL		442
# define ERRCODE_USERONCHANNEL		443
# define ERRCODE_NOLOGIN			444
# define ERRCODE_SUMMONDISABLED		445
# define ERRCODE_USERSDISABLED		446
# define ERRCODE_NOTREGISTERED		451
# define ERRCODE_NEEDMOREPARAMS		461
# define ERRCODE_ALREADYREGISTRED	462
# define ERRCODE_NOPERMFORHOST		463
# define ERRCODE_PASSWDMISMATCH		464
# define ERRCODE_YOUREBANNEDCREEP	465
# define ERRCODE_KEYSET				467
# define ERRCODE_CHANNELISFULL		471
# define ERRCODE_UNKNOWNMODE		472
# define ERRCODE_INVITEONLYCHAN		473
# define ERRCODE_BANNEDFROMCHAN		474
# define ERRCODE_BADCHANNELKEY		475
# define ERRCODE_NOPRIVILEGES		481
# define ERRCODE_CHANOPRIVSNEEDED	482
# define ERRCODE_CANTKILLSERVER		483
# define ERRCODE_NOOPERHOST			491
# define ERRCODE_UMODEUNKNOWNFLAG	501
# define ERRCODE_USERSDONTMATCH		502
# define ERRCODE_INVALIDCAP
# define ERRCODE_NOTOPIC
# define ERRCODE_BADCHANMASK
# define ERRCODE_ALREADYBAN
# define ERRCODE_SERVERISFULL
# define ERRCODE_KILLDENY

// Error messages
# define ERR_NOSUCHNICK(pseudo) (pseudo + " :No such nick/channel\r\n") //401
# define ERR_NOSUCHSERVER(server) (server + " :No such server\r\n") //402
# define ERR_NOSUCHCHANNEL(channel) (channel + " :No such channel\r\n") //403
# define ERR_CANNOTSENDTOCHAN(channel) (channel + " :Cannot send to channel\r\n") //404
# define ERR_TOOMANYCHANNELS(channel) (channel + " :You have joined too many channels\r\n") //405
# define ERR_WASNOSUCHNICK(nickname) (nickname + " :There was no such nickname\r\n") //406
# define ERR_TOOMANYTARGETS(dest) (dest + ":Duplicate recipients. No message delivered\r\n") //407
# define ERR_NOORIGIN() (":No origin specified\r\n") //409
# define ERR_NORECIPIENT(command) (":No recipient given (" + command + ")\r\n")
# define ERR_NOTEXTTOSEND() (":No text to send\r\n")
# define ERR_NOTOPLEVEL(mask) (mask + " :No toplevel domain specified\r\n")
# define ERR_WILDTOPLEVEL(mask) (mask + " :Wildcard in toplevel domain\r\n")
# define ERR_UNKNOWNCOMMAND(command) (command + " :Unknown command\r\n")
# define ERR_NOMOTD() (":MOTD File is missing\r\n")
# define ERR_NOADMININFO(server) (server + " :No administrative info available\r\n")
# define ERR_FILEERROR(operation, file) (":File error doing " + operation + " on " + file + "\r\n")
# define ERR_NONICKNAMEGIVEN() (":No nickname given\r\n")
# define ERR_ERRONEUSNICKNAME(pseudo) (pseudo + " :Erroneus nickname\r\n")
# define ERR_NICKNAMEINUSE(nick) (nick + " :Nickname is already in use\r\n")
# define ERR_NICKCOLLISION(nick, user, host) (nick + " :Nickname collision KILL from " + user + "@" + host + "\r\n")
# define ERR_USERNOTINCHANNEL(pseudo, channel) (pseudo + " :Is not on channel " + channel + "\r\n")
# define ERR_NOTONCHANNEL(channel) (channel + " :You're not on that channel\r\n")
# define ERR_USERONCHANNEL(user, channel) (user + channel + " :User is already on that channel\r\n")
# define ERR_NOLOGIN(user) (user + " :User not logged in\r\n")
# define ERR_SUMMONDISABLED() (":SUMMON has been disabled\r\n")
# define ERR_USERSDISABLED() (":USERS has been disabled\r\n")
# define ERR_NOTREGISTERED() (":You have not registered\r\n")
# define ERR_NEEDMOREPARAMS(command) (command + " :Not enough parameters\r\n") // 461
# define ERR_ALREADYREGISTRED() (":Unauthorized command (already registered)\r\n") // 462
# define ERR_NOPERMFORHOST() (":Your host isn't among the privileged\r\n")
# define ERR_PASSWDMISMATCH() (":Password incorrect\r\n") // 464
# define ERR_YOUREBANNEDCREEP() (":You are banned from this server\r\n")
# define ERR_KEYSET(channel) (channel + " :Channel key already set\r\n")
# define ERR_CHANNELISFULL(channel) (channel + " :Cannot join channel (+l)\r\n")
# define ERR_UNKNOWNMODE(character) (character + " :is unknown mode char to me\r\n")
# define ERR_INVITEONLYCHAN(channel) (channel + " :Cannot join channel (+i)\r\n")
# define ERR_BANNEDFROMCHAN(channel) (channel + " :Cannot join channel (+b)\r\n")
# define ERR_BADCHANNELKEY(channel) (channel + " :Cannot join channel (+k)\r\n")
# define ERR_NOPRIVILEGES() (":Permission Denied- You're not an IRC operator\r\n") // 481
# define ERR_CHANOPRIVSNEEDED(channel) (channel + " :You're not channel operator\r\n")
# define ERR_CANTKILLSERVER() (":You cant kill a server!\r\n")
# define ERR_NOOPERHOST() (":No O-lines for your host\r\n")
# define ERR_UMODEUNKNOWNFLAG() (":Unknown MODE flag\r\n")
# define ERR_USERSDONTMATCH() (":Cannot change mode for other users\r\n")
# define ERR_INVALIDCAP(command) (command + " :Invalid CAP command\r\n")
# define ERR_NOTOPIC(channel) (channel + " :No topic is set\r\n")
# define ERR_BADCHANMASK(channel) (channel + " :Bad Channel Mask\r\n")
# define ERR_ALREADYBAN(channel, user) (channel + " " + user + " b :Channel " + channel + " list already contains " + user + "\r\n")
# define ERR_SERVERISFULL(serv_name) (serv_name + " Server is full\r\n");
# define ERR_KILLDENY(mssg) (":" + mssg + "\r\n")

#endif