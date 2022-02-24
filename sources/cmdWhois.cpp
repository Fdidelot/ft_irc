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

void	Command::_whois(std::stringstream& completeCommand, User& user) {

	std::string mask;
    std::strnig comma;
    
    completeCommand >> mask >> comma;
    User *tmp;
    while (!(mask.empty()))
    {
        if (tmp = findByNickName(user, name))
        {
            if (tmp)
                printUserData(tmp);
            else
            {
                sendDirect(user, ERRCODE_NOSUCHNICK, NOSUCHNICK(mask));
            }
        }
        completeCommand >> comma;
        if (comma.empty())
            return;
        completeCommand >> mask;
    }

}
