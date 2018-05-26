#ifndef SHELL_EXECUTOR_H
#define SHELL_EXECUTOR_H

#include <string>
#include <vector>
#include <pwd.h>
#include <unistd.h>
#include <cstdlib>
#include <sys/stat.h>
#include <iostream>

using std::string;
using std::vector;

struct Redirection {
    string path;
    int descriptor;
};

struct Command {
    string app;
    vector<string> params;
    vector<Redirection> redirections;
    bool foreground;
};

class Executor {
public:
    int execute(Command&);
    int execute(vector<Command>);
};


#endif //SHELL_EXECUTOR_H
