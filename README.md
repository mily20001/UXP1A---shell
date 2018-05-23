# UXP1A---shell
Interactive Linux command interpreter

Uwaga omawiam po kolei : 

main.cpp - uruchamia terminal, a żeby było pięknie to terminal jest singletonem

Terminal.h - wyświetla prompt z datą, nazwą użytkownika, katalogiem i czym tam będziemy chcieli.

Parser.h - pobiera łańcuch znaków, ale jak jest za długi to zgłasza wyjątek. Póki co jest parser jest w stanie pobierać znaki, rozpoznawać słowa kluczowe, rozpoznawać identyfikatory i operatory. Zostały do napisania poszczególne metody 'parse_xxx'.
Parser ma takie funkcje jak :
    > nextChar - pobiera następny znak
    > nextSymbol - pobiera cały token (słowo kluczowe, operator, identyfikator)
    > parse - główna funckcja, która zwróci do Terminala listę Statementów, które potem trzeba wykonać mając już w nich określone jasno co       jest czym
    > metody parse_xxx - są takimi pomocnikami metody parse, zwracają odpowiednie Statementy. np. parse_change_direcotry zwróci                 CdStatement, w którym będzie zapisana ścieżka, która była po słowie kluczowym cd

Statement.h - tu będzie dużo różnych rodzajów Statementów dziedziczących po Statement
