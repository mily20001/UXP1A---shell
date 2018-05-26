#ifndef CDSTATEMENT_H
#define CDSTATEMENT_H

#include "../Statement.h"

class CdStatement : public Statement
{
public:
    CdStatement(std::list<std::string> _argList)
    {
        argList = _argList;
    }
    void execute()
    {
        std::cout << "wykonuje cd" << std::endl;
    }
};

#endif //CDSTATEMENT_H
