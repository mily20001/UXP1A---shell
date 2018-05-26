#ifndef EXPORTSTATEMENT_H
#define EXPORTSTATEMENT_H

#include "Statement.h"

class ExportStatement : public Statement
{
public:
    ExportStatement(std::list<std::string> _argList)
    {
        argList = _argList;
    }
    void execute()
    {
        std::cout << "wykonuje export" << std::endl;
    }
};

#endif //EXPORTSTATEMENT_H
