#ifndef UNTITLED1_OUTSTATEMENT_H
#define UNTITLED1_OUTSTATEMENT_H

#include "../Statement.h"

class OutStatement : public Statement
{
public:
    OutStatement(std::list<std::string> _argList)
    {
        argList = _argList;
    }
    void execute()
    {
        std::cout << "wykonuje out" << std::endl;
    }
};

#endif //UNTITLED1_OUTSTATEMENT_H
