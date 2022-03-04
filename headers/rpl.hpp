/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rpl.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdidelot <fdidelot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 21:37:11 by fdidelot          #+#    #+#             */
/*   Updated: 2022/03/04 21:39:13 by fdidelot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPL_HPP
# define RPL_HPP

/*
**  reponse for command file
*/
// Handmade responses
# define PONG			-1
# define PONG_MSG(servName) (":" + servName + " PONG " + servName + " :" + servName + "\r\n")
# define NICK_MSG(nick, user_name) (":" + user_name + "! NICK " + nick + "\r\n")

// Response codes
# define RPLCODE_MESSAGE
# define RPLCODE_WELCOME			1
# define RPLCODE_YOURHOST			2
# define RPLCODE_CREATED			3
# define RPLCODE_MYINFO				4
# define RPLCODE_BOUNCE				5
# define RPLCODE_NONE				300
# define RPLCODE_USERHOST			302
# define RPLCODE_ISON				303
# define RPLCODE_AWAY				301
# define RPLCODE_UNAWAY				305
# define RPLCODE_NOWAWAY			306
# define RPLCODE_WHOISUSER			311
# define RPLCODE_WHOISOPERATOR		313
# define RPLCODE_WHOISIDLE			317
# define RPLCODE_WHOREPLY			352
# define RPLCODE_ENDOFWHOIS			318
# define RPLCODE_WHOISCHANNELS		319
# define RPLCODE_WHOWASUSER			314
# define RPLCODE_ENDOFWHOWAS		369
# define RPLCODE_LISTSTART			321
# define RPLCODE_LIST				322
# define RPLCODE_LISTEND			323
# define RPLCODE_CHANNELMODEIS		324
# define RPLCODE_NOTOPIC			331
# define RPLCODE_TOPIC				332
# define RPLCODE_INVITING			341
# define RPLCODE_SUMMONING			342
# define RPLCODE_VERSION			351
# define RPLCODE_ENDOFWHO			315
# define RPLCODE_NAMREPLY			353
# define RPLCODE_ENDOFNAMES			366
# define RPLCODE_LINKS				364
# define RPLCODE_ENDOFLINKS			365
# define RPLCODE_BANLIST			367
# define RPLCODE_ENDOFBANLIST		368
# define RPLCODE_INFO				371
# define RPLCODE_ENDOFINFO			374
# define RPLCODE_MOTDSTART			375
# define RPLCODE_MOTD				372
# define RPLCODE_ENDOFMOTD			376
# define RPLCODE_YOUREOPER			381
# define RPLCODE_REHASHING			382
# define RPLCODE_TIME				391
# define RPLCODE_USERSSTART			392
# define RPLCODE_ENDOFUSERS			394
# define RPLCODE_NOUSERS			395
# define RPLCODE_TRACELINK			200
# define RPLCODE_TRACECONNECTING	201
# define RPLCODE_TRACEHANDSHAKE		202
# define RPLCODE_TRACEUNKNOWN		203
# define RPLCODE_TRACEOPERATOR		204
# define RPLCODE_TRACEUSER			205
# define RPLCODE_TRACESERVER		206
# define RPLCODE_TRACENEWTYPE		208
# define RPLCODE_TRACELOG			261
# define RPLCODE_TRACEEND			262
# define RPLCODE_STATSLINKINFO		211
# define RPLCODE_STATSCOMMANDS		212
# define RPLCODE_STATSCLINE			213
# define RPLCODE_STATSNLINE			214
# define RPLCODE_STATSILINE			215
# define RPLCODE_STATSKLINE			216
# define RPLCODE_STATSYLINE			218
# define RPLCODE_ENDOFSTATS			219
# define RPLCODE_STATSLLINE			241
# define RPLCODE_STATSUPTIME		242
# define RPLCODE_STATSOLINE			243
# define RPLCODE_STATSHLINE			244
# define RPLCODE_UMODEIS			221
# define RPLCODE_LUSERCLIENT		251
# define RPLCODE_LUSEROP			252
# define RPLCODE_LUSERUNKNOWN		253
# define RPLCODE_LUSERCHANNELS		254
# define RPLCODE_LUSERME			255
# define RPLCODE_ADMINME			256
# define RPLCODE_ADMINLOC1			257
# define RPLCODE_ADMINLOC2			258
# define RPLCODE_ADMINEMAIL			259
# define RPLCODE_CREATIONTIME
# define RPLCODE_YOURESERVICE		383

// Response text
# define RPL_MESSAGE(servName, number, nick) (":" + servName + " " + number + " " + nick + " ")
# define RPL_MYINFO(servName, servVersion) (":" + servName + " " + servVersion + " user_mode, channel modes" + "\r\n")
# define RPL_WELCOME(nick) (":Welcome to the Internet Relay Network " + nick + "\r\n")
# define RPL_YOURHOST(servName, servVersion) (":Your host is " + servName + ", running version " + servVersion + "\r\n")
# define RPL_CREATED(date) (":This server was created " + date + "\r\n")
# define RPL_BOUNCE(server_name, port) ("Try server " + server_name + ", port " + port + "\r\n")
# define RPL_NONE() ("\r\n") //300
# define RPL_USERHOST(userhost_list) (userhost_list + "\r\n") //<réponse> ::= <pseudo>['*'] '=' <'+'|'-'><hôte>
# define RPL_ISON(user_list) (user_list + "\r\n")
# define RPL_AWAY(pseudo, str) (pseudo + " " + str + "\r\n")
# define RPL_UNAWAY() (":You are no longer marked as being away\r\n")
# define RPL_NOWAWAY() (":You have been marked as being away\r\n")
# define RPL_WHOISUSER(nick, user, host, realname) (nick + " " + user + " " + host + " * :" + realname + "\r\n")
# define RPL_WHOISOPERATOR(pseudo) (pseudo + " :is an IRC operator\r\n")
# define RPL_WHOISIDLE(pseudo, idle, signon) (pseudo + " " + idle + " " + signon + " :seconds idle, signon time\r\n")
# define RPL_WHOREPLY(arg) (arg + "\r\n")
# define RPL_ENDOFWHOIS(pseudo) (pseudo + " :End of /WHOIS list\r\n")
# define RPL_WHOISCHANNELS(nick, chann_info) (nick + " :" + chann_info + "\r\n")
# define RPL_WHOWASUSER(nick, user, host, realname) (nick + " " + user + " " + host + " * :" + realname + "\r\n")
# define RPL_ENDOFWHOWAS(nick) (nick + " :End of WHOWAS\r\n")
# define RPL_LISTSTART() ("Channel :Users Name\r\n")
# define RPL_LIST(channel, topic) (channel + " :" + topic + "\r\n")
# define RPL_LISTEND() (":End of LIST\r\n")
# define RPL_CHANNELMODEIS(channel, mode, params) (channel + " " + mode + " " + params + "\r\n")
# define RPL_NOTOPIC(channel) (channel + " :No topic is set\r\n")
# define RPL_TOPIC(channel, subject) (channel + " :" + subject + "\r\n")
# define RPL_INVITING(channel, pseudo) (channel + " " + pseudo + "\r\n")
# define RPL_SUMMONING(user) (user + " :Summoning user to IRC\r\n")
# define RPL_VERSION(version, debuglevel, server, comment) (version + "." + debuglevel + " " + server + " :" + comment + "\r\n")
# define RPL_ENDOFWHO(name) (name + " :End of WHO list\r\n")
# define RPL_NAMREPLY(channel, nick_list) (channel + " :" + nick_list + "\r\n") //modif_ici
# define RPL_ENDOFNAMES(channel) (channel + " :End of NAMES list\r\n")
# define RPL_LINKS(mask, server_name, hopcount, info) (mask + " " + server_name + " " + hopcount + " " + info + "\r\n")
# define RPL_ENDOFLINKS(mask) (mask + " :End of LINKS list\r\n")
# define RPL_BANLIST(mssg) (mssg + "\r\n")
# define RPL_ENDOFBANLIST(channel) (channel + " :End of list\r\n")
# define RPL_INFO(info) (":" + info + "\r\n")
# define RPL_ENDOFINFO() (":End of INFO list\r\n")
# define RPL_MOTDSTART(server) (":- " + server + " Message of the day - \r\n")
# define RPL_MOTD(comment) (":- " + comment + "\r\n")
# define RPL_ENDOFMOTD() (":End of MOTD command\r\n")
# define RPL_YOUREOPER() (":You are now an IRC operator\r\n") // 381
# define RPL_REHASHING(config_file) (config_file + " :Rehashing\r\n")
# define RPL_TIME(server, time_serveur) (server + " :" + time_serveur + "\r\n")
# define RPL_USERSSTART() (":UserID Terminal Hôte\r\n")
# define RPL_ENDOFUSERS() (":End of users\r\n")
# define RPL_NOUSERS() (":Nobody logged in\r\n")
# define RPL_TRACELINK(dest, next_serv) ("Link " + std::string(VERSION) + " " + dest + " " + next_serv + "\r\n")
# define RPL_TRACECONNECTING(classe, server) ("Try. " + classe + " " + server + "\r\n")
# define RPL_TRACEHANDSHAKE(classe, server) ("H.S. " + classe + " " + serveur + "\r\n")
# define RPL_TRACEUNKNOWN(pseudo) ("???? 1 " + pseudo + "\r\n")
# define RPL_TRACEOPERATOR(pseudo) ("Oper 1 " + pseudo + "\r\n")
# define RPL_TRACEUSER(pseudo) ("User 1 " + pseudo + "\r\n")
# define RPL_TRACESERVER(server_name) ("Serv 1 0S 0C " + server_name + " *!*@" + server_name + " V" + PROTOCOL_VERSION + "\r\n")
# define RPL_TRACENEWTYPE(new_type, name) (new_type + " 0 " + name + "\r\n")
# define RPL_TRACELOG(file_log, debug_level) ("File " + file_log + " " + debug_level + "\r\n")
# define RPL_TRACEEND(server_name, version_debug) (server_name + " " + version_debug + " :End of TRACE\r\n")
# define RPL_STATSLINKINFO(arg) (arg + "\r\n")
# define RPL_STATSCOMMANDS(arg) (arg + "\r\n")
# define RPL_STATSCLINE(host, name, port, classe) ("C " + host + " * " + name + " " + port + " " + classe + "\r\n")
# define RPL_STATSNLINE(host, name, port, classe) ("N " + host + " * " + name + " " + port + " " + classe + "\r\n")
# define RPL_STATSILINE(host, port, classe) ("I " + host + " * " + host + " " + port + " " + classe + "\r\n")
# define RPL_STATSKLINE(host, user_name, port, classe) ("K " + host + " * " + user_name + " " + port + " " + classe + "\r\n")
# define RPL_STATSYLINE(classe, frq_ping, frq_connection, sendq_max) ("Y " + classe + " " + frq_ping + " " + frq_connection + " " + sendq_max + "\r\n")
# define RPL_ENDOFSTATS(stat_letter) (stat_letter + " :End of STATS report\r\n")
# define RPL_STATSLLINE(host_mask, server_name, max_depth) ("L " + host_mask + " * " + server_name + max_depth "\r\n")
# define RPL_STATSUPTIME(arg) (":Server Up " + arg + "\r\n")
# define RPL_STATSOLINE(host_mask, name) ("O " + host_mask + " * " + name + "\r\n")
# define RPL_STATSHLINE(host_mask, server_name) ("H " + host_mask + " * " + server_name + "\r\n")
# define RPL_UMODEIS(user_mode) ("+" + user_mode + "\r\n")
# define RPL_LUSERCLIENT(int1, int2, int3) (":There are " + int1 + " users and " + int2 + " invisible on " + int3 + " servers\r\n")
# define RPL_LUSEROP(int1) (int1 + " :operator(s) online\r\n")
# define RPL_LUSERUNKNOWN(int1) (int1 + " :unknown connection(s)\r\n")
# define RPL_LUSERCHANNELS(int1) (int1 + " :channels formed\r\n")
# define RPL_LUSERME(int1, int2) (":I have " + int1 + " clients and " + int2 + " servers\r\n")
# define RPL_ADMINME(server) (server + " :Administrative info\r\n")
# define RPL_ADMINLOC1(info) (":" + info + "\r\n")
# define RPL_ADMINLOC2(info) (":" + info + "\r\n")
# define RPL_ADMINEMAIL(info) (":" + info + "\r\n")
# define RPL_CREATIONTIME(channel, c_time) (channel + " " + c_time + "\r\n")
# define RPL_YOURESERVICE(servicename) (":You are service " + servicename + "\r\n")

#endif