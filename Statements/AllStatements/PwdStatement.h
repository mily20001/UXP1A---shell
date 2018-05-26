#ifndef UNTITLED1_PWDSTATEMENT_H
#define UNTITLED1_PWDSTATEMENT_H

#include "../Statement.h"

class PwdStatement : public Statement
{
public:
    PwdStatement(std::list<std::string> _argList)
    {
        argList = _argList;
    }
    void execute()
    {
        std::cout << "wykonuje pwd" << std::endl;
    }
};


#endif //UNTITLED1_PWDSTATEMENT_H
