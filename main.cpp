#include <iostream>
#include <ctime>

#include "Terminal.h"

int main()
{
    Terminal::getInstance().start("dominik","/home");
    return 0;
}

