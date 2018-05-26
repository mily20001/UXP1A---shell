#ifndef ENVSTATEMENT_H
#define ENVSTATEMENT_H

#include "../Statement.h"

class EnvStatement : public Statement
{
public:
    EnvStatement(std::list<std::string> _argList)
    {
        argList = _argList;
    }
    void execute()
    {
        std::cout << "wykonuje env" << std::endl;
    }
};


#endif //ENVSTATEMENT_H
