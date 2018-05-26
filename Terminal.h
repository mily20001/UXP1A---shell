#ifndef TERMINAL_H
#define TERMINAL_H

#include <unistd.h>
#include <sstream>
#include <vector>

#include "Parser.h"
#include "Executor.h"

using std::string;
using std::cout;
using std::endl;
using std::vector;

const string currentDateTime()
{
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[10];
    tstruct = *localtime(&now);
    strftime(buf, 10, "%X", &tstruct);

    return string(buf);
}

const string getUserName() {
    return string(getlogin());
}

const string getHostName() {
    char hostname[64];
    if(gethostname(hostname, 63) != -1) {
        hostname[63] = 0;
        return string(hostname);
    }

    return "unknown";
}

const string getCurrentDir() {
    char path[300];
    if(getcwd(path, 299) != NULL) {
        path[299] = 0;
        return string(path);
    }

    return "error"; // xD
}

class Terminal
{
public :
    static Terminal& getInstance()
    {
        static Terminal instance;
        return instance;
    }
    void start()
    {
        while(true)
        {
            try {
                std::cout << "[" << currentDateTime() << "] " << getUserName() <<"@"<< getHostName() << " " << getCurrentDir() <<"> " ;
                std::getline(std::cin, input);
//                Parser parser;
//                parser.parse(input);

                string word;
                std::istringstream iss(input, std::istringstream::in);

                Command cmd;

                iss >> cmd.app;

                while( iss >> word )
                {
                    cmd.params.push_back(word);
                }

                Executor executor;
                executor.execute(cmd);
            } catch(std::exception &e) {
                std::cout << "Nie rozpoznano polecenia." << std::endl;
                break; //remove
            }
        }
    }
private:
    Terminal() {};
    Terminal(Terminal const&) {};
    Terminal& operator=(Terminal const&) {};
    static Terminal *instance;

    string input;

};
#endif // TERMINAL_H
