#include "Command.hpp"

User    *findUserByNickName(User& user, std::string name)
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

void    Command::printUserData(User& user, User& target)
{
    std::string nick = target.getNick();
    std::string username = target.getUsername();
    std::string host = SERV_NAME;
    std::string realname = target.getRealname();

    sendCommand(user, RPLCODE_WHOISUSER, RPL_WHOISUSER(nick, username, host, realname));
    
    std::list<Channel *> tmp =  target.getChannelList();
    std::list<Channel *>::iterator it = tmp.begin();
    std::list<Channel *>::iterator ite = tmp.end();
    while (it != ite)
    {
        sendCommand(user, RPLCODE_WHOISCHANNELS, RPL_WHOISCHANNELS((*it)->getName(), "")); // A remplacer par le topic du chann
        it++;
    }
    if (target.getMode('o') == true)
        sendCommand(user, RPLCODE_WHOISOPERATOR, RPL_WHOISOPERATOR(nick));
    //    sendCommand(user, RPLCODE_WHOISIDLE, RPL_WHOISIDLE()) Je sais pas, signon relou mais le reste ez
    sendCommand(user, RPLCODE_ENDOFWHOIS, RPL_ENDOFWHOIS(nick));
}

void	Command::_whois(std::stringstream& completeCommand, User& user) {

    //Add idle ?

    //(void)completeCommand; (void)user;
	std::string mask;
    std::string comma;
    
    completeCommand >> mask;
    User *tmp;
    while (!(mask.empty()))
    {
        if ((tmp = findUserByNickName(user, mask)) != NULL)
        {
            if (tmp)
                printUserData(user, *tmp);
            else
            {
                sendCommand(user, ERRCODE_NONICKNAMEGIVEN, ERR_NONICKNAMEGIVEN());
                return;
            }
        }
        completeCommand >> comma;
        if (comma.empty() || comma != ",")
            return;
        completeCommand >> mask;
    }
}
