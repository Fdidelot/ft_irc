#include "Command.hpp"

User    *findByNickName(User& user, std::string name)
{
    std::map<int, User> tmp = user.getServer().getUsers();
    std::map<int, User>::iterator it = tmp.begin();
    std::map<int, User>::iterator ite = tmp.end();
    while (it != ite)
    {
        if (it->second.getNick() == name)
            return (&(it->second));
        it++;
    }
    return NULL;
}

void	Command::_kill(std::stringstream& completeCommand, User& user)
{
    std::string cmd = "KILL";
    std::string nick;
    std::string message;
    User *target;

    completeCommand >> nick;
    completeCommand >> message;
    if (user.getMode('o') == false)
    {
        sendCommand(user, 481, ERR_NOPRIVILEGES());
        return ;
    }
    if (nick.empty() == true || message.empty())
    {
        sendCommand(user, 461, ERR_NEEDMOREPARAMS(cmd));
        return ;
    }
    if (nick == SERV_NAME)
    {
        sendCommand(user, ERRCODE_CANTKILLSERVER, ERR_CANTKILLSERVER());
        return ;
    }
    target = findByNickName(user, nick);
    if (!target)
    {
        sendCommand(user, ERRCODE_NOSUCHNICK, ERR_NOSUCHNICK(nick));
        return ;
    }
    sendCommand(tmp, PONG, "You have been killed because: " + message);
    user.getServer().endConnection(target.getFd());
    std::cout << "Oui avec des amis!\n";
}