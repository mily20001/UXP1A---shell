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
 * Muszę też w funkcjach setUser() i setDir() dopisać wczytywanie jakaś funkcją typu gethostname().
 *
 */

#include "Parser.h"

class Terminal
{
public :
    static Terminal& getInstance()
    {
        static Terminal instance;
        return instance;
    }
    const std::string currentDateTime()
    {
        time_t now = time(nullptr);
        struct tm tstruct;
        char buf[80];
        tstruct = *localtime(&now);
        strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
        return buf;
    }
    void setUser()
    {
        user = "dominik";
    }
    void setDir()
    {
        dir = "/home";
    }
    void start()
    {
        Parser parser;
        while(true)
        {
            try {
                setUser();
                setDir();
                std::cout << "[" << currentDateTime() << "]" << user <<"@ubuntu" << dir <<">" ;
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

    std::string user;
    std::string dir;
    std::string input;

};
#endif // TERMINAL_H
