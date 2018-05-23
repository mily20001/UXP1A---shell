#ifndef TERMINAL_H
#define TERMINAL_H

#include "Parser.h"

const std::string currentDateTime()
{
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

    return buf;
}

class Terminal
{
public :
    static Terminal& getInstance()
    {
        static Terminal instance;
        return instance;
    }
    void start(std::string _user, std::string _dir)
    {
        user = _user;
        dir = _dir;
        while(true)
        {
            try{
                std::cout << "[" << currentDateTime() << "]" << user <<"@ubuntu" << dir <<">" ;
                std::getline(std::cin,input);
                Parser parser;
                parser.parse(input);
            }catch(std::exception &e){
                std::cout << "Nie rozpoznano polecenia." << std::endl;
            }
        }
    }
private:
    Terminal() {};
    Terminal(Terminal const&) {};
    Terminal& operator=(Terminal const&) {};
    static Terminal *instance;

    std::string user;
    std::string dir;
    std::string input;

};
#endif // TERMINAL_H
