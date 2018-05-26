#ifndef LSSTATEMENT_H
#define LSSTATEMENT_H

#include "Statement.h"

class LsStatement : public Statement
{
public:
    LsStatement(std::list<std::string> _argList)
    {
        argList = _argList;
    }
    void execute()
    {
        std::cout << "wykonuje ls" << std::endl;
    }
};

#endif //LSSTATEMENT_H
