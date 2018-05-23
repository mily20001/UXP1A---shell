#ifndef PARSER_H
#define PARSER_H

#include <cstring>
#include <cstdlib>
#include <list>

#include "Statement.h"

const int MAXIDENTSIZE = 10;
const int MAXLINESIZE = 500;

enum SymType { cdsy, lssy, exportsy, pwdsy, exitsy, fgsy, bgsy, outsy, insy, pipesy, identsy, escsy, exesy, commasy, EOL, othersy };

class Parser
{
public :
    char nextChar()
    {
        activeChar++;
    }
    void skipWhiteSpace()
    {
        while(isspace((int)(*activeChar))) nextChar();
    }
    SymType KeyWord()
    {
        if(strcmp(spellIdent, "cd") == 0)
            return cdsy;
        if(strcmp(spellIdent, "ls") == 0)
            return lssy;
        if(strcmp(spellIdent, "export") == 0)
            return exportsy;
        if(strcmp(spellIdent, "pwd") == 0)
            return pwdsy;
        if(strcmp(spellIdent, "exit") == 0)
            return exitsy;
        if(strcmp(spellIdent, "fg") == 0)
            return fgsy;
        if(strcmp(spellIdent, "bg") == 0)
            return bgsy;
        return identsy;
    }
    SymType nextSymbol()
    {
        skipWhiteSpace();
        int lenght = 0;
        if(*activeChar == '\n')
            return EOL;
        if(*activeChar == '>')
            return outsy;
        if(*activeChar == '<')
            return insy;
        if(*activeChar == '|')
            return pipesy;
        if(*activeChar == '\\')
            return escsy;
        if(*activeChar == '\'')
            return commasy;
        if(*activeChar == '.')
        {
            activeChar++;
            if(*activeChar == '/')
                return exesy;
            else
                activeChar--;
        }
        while(isalnum((int)(*activeChar)))
        {
            spellIdent[lenght++] = *activeChar;
            nextChar();
            if(lenght > MAXIDENTSIZE){
                throw std::exception();
            }
        }
        spellIdent[lenght] = '\0';
        return KeyWord();
    }

    Statement* parse_change_direcotory() {};
    Statement* parse_list_direcotory() {};
    Statement* parse_print_working_directory() {};
    Statement* parse_exit() {};
    Statement* parse_foreground() {};
    Statement* parse_background() {};
    Statement* parse_excec() {};
    Statement* parse_stdin_redirect() {};

    std::list<Statement*> parse(std::string _input)
    {
        input = _input;
        if(input.length() > MAXLINESIZE)
        {
            std::cout << "Polecenie jest za dlugie" << std::endl;
            throw std::exception();
        }
        activeChar = input.begin();
        activeSym = nextSymbol();
        std::list<Statement*> statementList;
        try {
            switch(activeSym){
                case cdsy:
                    statementList.push_back(parse_change_direcotory());
                    break;
                case lssy:
                    statementList.push_back(parse_list_direcotory());
                    break;
                case pwdsy:
                    statementList.push_back(parse_print_working_directory());
                    break;
                case exitsy:
                    statementList.push_back(parse_exit());
                    break;
                case fgsy:
                    statementList.push_back(parse_foreground());
                    break;
                case bgsy:
                    statementList.push_back(parse_background());
                    break;
                case exesy:
                    statementList.push_back(parse_excec());
                    break;
                case insy:
                    statementList.push_back(parse_stdin_redirect());
                    break;
                case identsy:
                    statementList.push_back(parse_excec());
                    break;
                case EOL:
                    return statementList;
                default:
                    throw std::exception();
            }
        }catch(std::exception &e){
            std::cout << "Nieprawidłowe polecenie!" << std::endl;
            throw std::exception();
        }
    }
private:
    std::string input;
    std::string::iterator activeChar;
    SymType activeSym;
    char spellIdent[MAXIDENTSIZE];
};

#endif // PARSER_H

