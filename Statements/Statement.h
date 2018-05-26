#ifndef STATEMENT_H
#define STATEMENT_H

/*
 *  Created by Dominik on 26.05.2018.
 *
 * ================= OPIS =================
 *
 * W tej klasie definiujemy Statementy (czyli tak jakby polecenia).
 *
 * Utworzyłem kilka pierwszych klas, którym trzeba uzupełnić metody execute().
 *
 * ================= JAK WYPELNIC METODE EXECUTE() =================
 *
 * Jeśli chcemy wypełnić metodę execute() to :
 *
 *      > wchodzimy do odpowiedniej klasy XxxStatement
 *
 *      > wypełniamy metodę, jeśli potrzebujemy dodatkowo jakąś klasę to załączamy ją jej plik nagłówkowy w XxxStatement
 *
 *      > metoda może rzucać wyjątki, które definiujemy w Exception.h
 *
 *      > UWAGA - parser rozpoznał tylko słowo/znak kluczowy który rozpoczyna nasze polecenie, potem wczytywał arguemnty jak leci,
 *                do znaku końca linii lub pipe'a. Jest głupim parserem i nie zastanawiał się jakie to argumenty,
 *                czy są poprawne, czy są w dobrej kolejności, etc. to musi zweryfikować metoda execute i jeśli stwierdzi, że
 *                coś jest nie tak to powinna rzucić SemanticException(), a jeśli stwierdzi, że jest ok to może przejść
 *                do właściwego wykonania
 *
 * ================= JAK UTWORZYC NOWY STATEMENT =================
 *
 * Jeśli chcemy utworzyć nowy Statement to :
 *
 *      > dodajemy nowy, unikalny enum do SymType (np. xxxsy)
 *
 *      > jeśli nasze polecenie wykorzystuje słowo kluczowe (np. cd) to dodajemy odpowiednią parę w KeyWordMap np. ("xx", xxsy)
 *
 *      > jeśli nasze polecenie wykorzystuje znak specjalny to dodajemy odpowiednią parę w KeySignMap
 *        UWAGA - znaki specjalne dzielimy tylko na dwa typy :
 *          - takie po których nie może być białego znaku np. $
 *          - takie po których musi być biały znak np. < (w takim przypadku stawiamy spację w KeySignMap)
 *
 *      > tworzymy klasę XxxStatement dziedziczącą po Statement, która dostarcza konstruktor i metodę execute()
 *
 *      > załączamy plik nagłówkowy XxxStatement.h w pliku Parser.h
 *
 *      > w pliku Parser.h odnajdujemy funkcję properStatement i dodajemy tam 2 linijki :
 *              if(order == xxxsy)
 *                  return new XxxStatement(argList);
 *
 *      > implementujemy metodę execute()
 *
 *
 */

#include "Exception.h"

enum SymType { cdsy, lssy, exportsy, pwdsy, exitsy, fgsy, bgsy, outsy, envsy, exesy, identsy, EOLsy, STARTsy, othersy };

std::map<std::string,SymType> KeyWordMap
    {
        std::make_pair("cd", cdsy),
        std::make_pair("ls", lssy),
        std::make_pair("export", exportsy),
        std::make_pair("pwd", pwdsy),
        std::make_pair("exit", exitsy),
        std::make_pair("fg", fgsy),
        std::make_pair("bg", bgsy)
    };

std::map<std::string,SymType> KeySignMap
    {
        std::make_pair("./", exesy),
        std::make_pair("$", envsy),
        std::make_pair("< ", outsy)
    };

class Statement
{
public:
    Statement() {};
    virtual ~Statement() {}
    virtual void execute() {};
protected:
    std::list<std::string> argList;
};


#endif // STATEMENT_H
