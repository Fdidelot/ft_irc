#include "Command.hpp"

bool     findCommonChannel(User u1, User u2)
{
    std::list<Channel *>::iterator it1 = u1.getChannel().begin();
    std::list<Channel *>::iterator ite1 = u1.getChannel().end();

    std::list<Channel *>::iterator it2 = u2.getChannel().begin();
    std::list<Channel *>::iterator ite2 = u2.getChannel().end();
    while (it1 != ite1)
    {
        while (it2 != ite2)
        {
            if (it1->getName() == it2->getName())
                return (false);
            it2++;
        }
        it2 = u2.getChannel().begin();
        it1++;
    }
    return (true);
}

void	Command::_who(std::stringstream& completeCommand, User& user) {

	std::string mask;
    std::strnig tmp;
    
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
                    printUserDatas(it->second);
            it++
        }
    
    }

}
