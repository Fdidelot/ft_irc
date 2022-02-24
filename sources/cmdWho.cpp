#include "Command.hpp"

bool     findCommonChannel(User u1, User u2)
{
    std::list<Channel *>::iterator it1 = u1.getChannelList().begin();
    std::list<Channel *>::iterator ite1 = u1.getChannelList().end();

    std::list<Channel *>::iterator it2 = u2.getChannelList().begin();
    std::list<Channel *>::iterator ite2 = u2.getChannelList().end();
    while (it1 != ite1)
    {
        while (it2 != ite2)
        {
            if ((*it1)->getName() == (*it2)->getName())
                return (false);
            it2++;
        }
        it2 = u2.getChannelList().begin();
        it1++;
    }
    return (true);
}

User    *findByNickname(User& user, std::string name)
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
/*
User    *findByHost(User& user, std::string name)
{
    std::map<int, User> tmp = user.getServer().getUsers();
    std::map<int, User>::iterator it = tmp.begin();
    std::map<int, User>::iterator ite = tmp.end();
    while (it != ite)
    {
        if (it->second.getHost() == name)
            return (&(it->second));
        it++;
    }
    return NULL;
}
*/
User    *findByUsername(User& user, std::string name)
{
    std::map<int, User> tmp = user.getServer().getUsers();
    std::map<int, User>::iterator it = tmp.begin();
    std::map<int, User>::iterator ite = tmp.end();
    while (it != ite)
    {
        if (it->second.getUsername() == name)
            return (&(it->second));
        it++;
    }
    return NULL;
}

std::string findByChannel(User *u1, std::string mask)
{
    std::list<Channel *>::iterator it = u1->getChannelList().begin();
    std::list<Channel *>::iterator ite = u1->getChannelList().end();
    std::string ret;
    ret.clear();

    while (it != ite)
    {
        if ((*it)->getName() == mask)
            return ((*it)->getName());
        it++;
    }
    return (ret);
}

void    Command::showAllUsers(User usr, std::map<int, User> users)
{
    std::map<int, User>::iterator it = users.begin();
    std::map<int, User>::iterator ite = users.end();

    while (it != ite)
    {
        sendCommand(usr, RPLCODE_WHOREPLY, RPL_WHOREPLY(createUserDataBuff(&(it->second))));
        it++;
    }
}

std::string createUserDataBuff(User *usr)
{
    std::string buff;

    buff += ':';
    buff += SERV_NAME;
    buff += ' ';
    buff += usr->getNick();
    buff += ' : ';
    buff += usr->getRealname();
    return buff;
}

void    Command::listUsersFromChannel(User usr, std::map<int, User> users, std::string chann)
{
    std::map<int, User>::iterator it = users.begin();
    std::map<int, User>::iterator ite = users.end();

    while (it != ite)
    {
        if ((findByChannel(&(it->second), chann).empty() == false))
            sendCommand(usr, RPLCODE_WHOREPLY, RPL_WHOREPLY(createUserDataBuff(&(it->second))));
        it++;
    }
}

//ADD gestion du 'o'
void	Command::_who(std::stringstream& completeCommand, User& user) {

	std::string mask;
    std::string tmp;
    
    completeCommand >> mask >> tmp;
    bool o = (tmp == "o") ? true : false;
    if (mask.empty() == true || mask == "0")
    {
        std::map<int, User> tmp = user.getServer().getUsers();
        std::map<int, User>::iterator it = tmp.begin();
        std::map<int, User>::iterator ite = tmp.end();
        while (it != ite)
        {
            if (it->second.getMode('i') == false)
                if (findCommonChannel(user, it->second) == true)
                sendCommand(user, RPLCODE_WHOREPLY, RPL_WHOREPLY(createUserDataBuff(&(it->second))));
            it++;
        }
        sendCommand(user, RPLCODE_ENDOFWHO, RPL_ENDOFWHO(user.getNick()));
    }
    else
    {
        if (findByChannel(&user, mask).empty() == false)
            listUsersFromChannel(user, user.getServer().getUsers(), mask);
        else if (findByNickname(user, mask) != NULL)
            sendCommand(user, RPLCODE_ENDOFWHO, RPL_ENDOFWHO(createUserDataBuff(findByNickname(user, mask))));
        else if (findByUsername(user, mask) != NULL)
            sendCommand(user, RPLCODE_ENDOFWHO, RPL_ENDOFWHO(createUserDataBuff(findByUsername(user, mask))));
        else if (mask == SERV_NAME)
            showAllUsers(user, user.getServer().getUsers());
        sendCommand(user, RPLCODE_ENDOFWHO, RPL_ENDOFWHO(user.getNick()));
    }
}
