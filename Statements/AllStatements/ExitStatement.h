#ifndef EXITSTATEMENT_H
#define EXITSTATEMENT_H

#include "Statement.h"

class ExitStatement : public Statement
{
public:
    ExitStatement(std::list<std::string> _argList)
    {
        argList = _argList;
    }
    void execute()
    {
        std::cout << "wykonuje exit" << std::endl;
        throw ExitException();
    }
};

#endif //EXITSTATEMENT_H
