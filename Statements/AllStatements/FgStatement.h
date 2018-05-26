#ifndef FGSTATEMENT_H
#define FGSTATEMENT_H

#include "../Statement.h"

class FgStatement : public Statement
{
public:
    FgStatement(std::list<std::string> _argList)
    {
        argList = _argList;
    }
    void execute()
    {
        std::cout << "wykonuje fg" << std::endl;
    }
};

#endif //FGSTATEMENT_H
