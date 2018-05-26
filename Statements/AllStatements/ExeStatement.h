#ifndef EXESTATEMENT_H
#define EXESTATEMENT_H

#include "../Statement.h"

class ExeStatement : public Statement
{
public:
    ExeStatement(std::list<std::string> _argList)
    {
        argList = _argList;
    }
    void execute()
    {
        std::cout << "wykonuje exe" << std::endl;
    }
};

#endif //EXESTATEMENT_H
