#ifndef PARSER_H
#define PARSER_H

/*
 *  Created by Dominik on 26.05.2018.
 *
 * ================= OPIS SKLADOWYCH =================
 *
 *  std::string input   - parsowane wejście
 *
 *  std::string::iterator activeChar    - obecnie parsowany znak
 *
 *  SymType activeSym   - obecnie parsowany symbol
 *
 *  std::string spellIdent      - ostatnio pobrane słowo
 *
 *  std::list<Statement*> statementList     - lista Statementów gotowych do wykonania
 *
 * ================= OPIS METOD =================
 *
 * Metody w parserze ustawione są w kolejności od najmniej do najbardziej złożonej.
 * Te wcześniejsze z reguły korzystają z tych póżniejszych :
 *
 * nextChar(), prevChar() - przesuwają wskaźnik który wskazuje na aktualnie parsowany znak
 *
 * skipWhiteSpace() - pomija białe znaki
 *
 * accept(char c) - zjada znak z wejścia, jeśli nie jest taki jak podany w argumencie to rzuca wyjątkiem
 *
 * KeyWord(), KeySign() - rozpoznają symbole specjalne (np. $) oraz komendy wbudowane (np. cd)
 *
 * nextArg() - wczytuje argument (np. /etc/pssswd)
 *
 * nextOrder() - rozpoznaje komendę (np. ls)
 *
 * nextStatement() - rozpoznaje całe polecenie razem z agrumentami (np. ls -l /etc/network/)
 *
 * properStatement() - z komendy i argumentaów tworzy odpowiedni tej komendzie Statement
 *
 * parse(std::string _input) - główna funkcja, która parsuje całą linię, tworzy listę Statementów z ich argumentami
 *
 * execute() - funkcja, która wykonuje polecenia w kolejności od lewej do prawej
 *
 */

#include "Statements/Statement.h"
#include "Statements/AllStatements/CdStatement.h"
#include "Statements/AllStatements/LsStatement.h"
#include "Statements/AllStatements/PwdStatement.h"
#include "Statements/AllStatements/EnvStatement.h"
#include "Statements/AllStatements/ExeStatement.h"
#include "Statements/AllStatements/FgStatement.h"
#include "Statements/AllStatements/OutStatement.h"
#include "Statements/AllStatements/BgStatement.h"
#include "Statements/AllStatements/ExitStatement.h"
#include "Statements/AllStatements/ExportStatement.h"

#include "Exception.h"

const int MAXIDENTSIZE = 100;
const int MAXLINESIZE = 500;

class Parser
{
public :

    char nextChar()
    {
        return *(activeChar++);
    }

    char prevChar()
    {
        return *(activeChar--);
    }

    void skipWhiteSpace()
    {
        while(isspace((int)(*activeChar)))
        {
            if(activeChar == input.end())
                break;
            nextChar();
        }
    }

    void accept(char c)
    {
        if(*activeChar == c)
            nextChar();
        else
            throw SemanticException();
    }

    SymType KeyWord()
    {
        for(auto iter = KeyWordMap.begin(); iter != KeyWordMap.end(); iter++)
        {
            if(spellIdent == (*iter).first)
            {
                return (*iter).second;
            }
        }
        return identsy;
    }

    SymType KeySign()
    {
        if(activeChar == input.end())
            return EOLsy;
        for(auto iter = KeySignMap.begin(); iter != KeySignMap.end(); iter++)
        {
            bool thisIsThatSign = true;
            int readChar = 0;
            for(auto stringIter = (*iter).first.begin(); stringIter != (*iter).first.end(); stringIter++)
            {
                if(*activeChar != *stringIter)
                {
                    thisIsThatSign = false;
                    break;
                }
                readChar++;
                nextChar();
            }
            if(thisIsThatSign)
            {
                if((*iter).first.back() != ' ')
                {
                    if(*activeChar != ' ')
                    {
                        return (*iter).second;
                    }
                } else
                {
                    return (*iter).second;
                }
            }
            for(int i = 0; i < readChar; i++)
            {
                prevChar();
            }
        }
        return othersy;
    }

    std::string nextArg()
    {
        skipWhiteSpace();
        std::string arg;
        arg.clear();
        while(!isspace((int)(*activeChar)) && *activeChar != '\0' && activeChar != input.end() && *activeChar != '|')
            arg.push_back(nextChar());
        return arg;
    }

    SymType nextOrder()
    {
        skipWhiteSpace();
        activeSym = KeySign();
        if(activeSym != othersy)
        {
            nextChar();
            return activeSym;
        }
        spellIdent.clear();
        do {
            spellIdent.push_back(*activeChar);
            nextChar();
            if(spellIdent.size() > MAXIDENTSIZE)
            {
                std::cout << "Identyfikator jest za dlugi" << std::endl;
                throw SemanticException();
            }
        }while(!isspace((int)(*activeChar)) && *activeChar != '\0');
        activeSym = KeyWord();
        return activeSym;
    }

    Statement* nextStatement()
    {
        auto order = nextOrder();
        std::list<std::string> argList;
        std::string arg;
        while(nextArg().size() != 0)
            argList.push_back(nextArg());
        return properStatement(order, argList);
    }

    std::list<Statement*> parse(std::string _input)
    {
        input = _input;
        activeChar = input.begin();
        activeSym = STARTsy;
        if(input.length() > MAXLINESIZE)
        {
            std::cout << "Polecenie jest za dlugie" << std::endl  << std::flush;
            throw SemanticException();
        }
        bool isStatement = false;
        while(*activeChar != '\0')
        {
            if(isStatement)
            {
                isStatement = false;
                accept('|');
                continue;
            }
            statementList.push_back(nextStatement());
            isStatement = true;
        }
        return statementList;
    }

    Statement* properStatement(SymType order,std::list<std::string> argList)
    {
        if(order == cdsy)
            return new CdStatement(argList);
        if(order == lssy)
            return new LsStatement(argList);
        if(order == pwdsy)
            return new PwdStatement(argList);
        if(order == exitsy)
            return new ExitStatement(argList);
        if(order == exportsy)
            return new ExportStatement(argList);
        if(order == fgsy)
            return new FgStatement(argList);
        if(order == bgsy)
            return new BgStatement(argList);
        if(order == envsy)
            return new EnvStatement(argList);
        if(order == outsy)
            return new OutStatement(argList);
        if(order == exesy)
            return new ExeStatement(argList);
        if(order == identsy)
            return new ExeStatement(argList);
    };

    void execute()
    {
        for(auto iter = statementList.begin(); iter != statementList.end(); iter++)
        {
            (*iter)->execute();
        }
        statementList.clear();
    }
private:
    std::string             input;
    std::string::iterator   activeChar;
    SymType                 activeSym;
    std::string             spellIdent;
    std::list<Statement*>   statementList;
};



#endif // PARSER_H
