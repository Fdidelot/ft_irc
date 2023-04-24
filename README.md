# ft_irc

`ft_irc` is an IRC (Internet Relay Chat) server implementation written in C++.

It is a group project part of the 42 curriculum.  
4 people contributed to this project:
- [fdidelot](https://github.com/Fdidelot)
- [mvidal-a](https://github.com/masakiva)
- [psemsari](https://github.com/psemsari)
- [bemoreau](https://github.com/Benj0t)

### Features

- Supports multiple simultaneous clients
- Implements common IRC commands
- Allows clients to join and leave channels
- Supports private messages between clients
- Provides error messages and status updates

### Usage

To start the server, you can run the following command:

```
./ft_irc [port] [password]
```

`port` is the port number on which the server will listen for incoming connections.  
`password` is the password used by the client to connect to the server. You can set anything you want.
