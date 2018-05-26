#ifndef TERMINAL_H
#define TERMINAL_H

/*
 *  Created by Dominik on 26.05.2018.
 *
 * ================= OPIS =================
 *
 * Ta klasa nie robi nic ciekawego. Po prostu uruchamia terminal i w kółko (do zamknięcia) wczytuje polecenia.
 *
 * Potem polecenie jest parsowane i wykonywane.
 *
 * Parsowanie i wykonanie polecenia może rzucić wyjątek, który jest tutaj łapany.
 *
 * W planach mam jeszcze dopisanie wątku, który będzie obsługiwał klawiaturę (np. strzałki w górę i w dół, ctrl+C).
 *
 */

#include <unistd.h>

#include "Parser.h"

using std::string;

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
    const string currentDateTime()
    {
        time_t     now = time(0);
        struct tm  tstruct;
        char       buf[10];
        tstruct = *localtime(&now);
        strftime(buf, 10, "%X", &tstruct);

        return string(buf);
    }
    void start()
    {
        Parser parser;
        while(true)
        {
            try {
                std::cout << "[" << currentDateTime() << "] " << getUserName() <<"@"<< getHostName() << " " << getCurrentDir() <<">" ;
                std::getline(std::cin,input);
                parser.parse(input);
                parser.execute();
                input.clear();
            }
            catch(ExitException &e)
            {
                std::cout << e.what() << std::endl;
                break;
            }
            catch(std::exception &e)
            {
                std::cout << e.what() << std::endl;
            }
        }
    }
private:
    Terminal() {};
    Terminal(Terminal const&) {};
    Terminal& operator=(Terminal const&) {};
    static Terminal* instance;

    std::string input;

};
#endif // TERMINAL_H
