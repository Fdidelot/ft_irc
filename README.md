# ft_irc

`ft_irc` is an IRC (Internet Relay Chat) server implementation written in C++.

It is a group project part of the 42 curriculum.  
4 people contributed to this project:
- [fdidelot](https://github.com/Fdidelot)
- [mvidal-a](https://github.com/masakiva)
- [psemsari](https://github.com/psemsari)
- [bemoreau](https://github.com/Benj0t)

### Usage

To start the server, you can run the following command:

```
./ft_irc [port] [password]
```

`port` is the port number on which the server will listen for incoming connections.  
`password` is the password used by the client to connect to the server. You can set anything you want.

You can use an IRC client such as `irssi` to connect to the server.

### Features

- Supports multiple simultaneous clients
- Implements common IRC commands (see below)
- Allows clients to join and leave channels
- Supports private messages between clients
- Provides error messages and status updates

Here is a list of the IRC commands implemented and available in this server :
- PASS
- NICK
- USER
- CAP
- MODE
- JOIN
- PING
- PRIVMSG
- PART
- QUIT
- OPER
- MOTD
- KILL
- WHOIS
- NOTICE

You can find the meaning of each command in [the documentation of the IRC protocol](https://www.rfc-editor.org/rfc/rfc2812).
