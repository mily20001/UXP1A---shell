#ifndef BGSTATEMENT_H
#define BGSTATEMENT_H

#include "Statement.h"

class BgStatement : public Statement
{
public:
    BgStatement(std::list<std::string> _argList)
    {
        argList = _argList;
    }
    void execute()
    {
        std::cout << "wykonuje bg" << std::endl;
    }
};

#endif //BGSTATEMENT_H
