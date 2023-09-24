#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <stack>

#include <cctype>

#include "AbstractOperatorFactory.hpp"
#include "AdditionOperatorFactory.hpp"
#include "SubtractionOperatorFactory.hpp"

template <typename T>
void printVector(std::vector<T> lines) {
    std::size_t count = lines.size();
    if (count == 0) {
        std::cout << "[]" << std::endl;
        return;
    }

    std::cout << '[' << lines[0];
    for (std::size_t i = 1; i < count; ++i) {
        std::cout << ", " << lines[i];
    }
    std::cout << ']' << std::endl;
}

bool stringContainsChar(std::string const & str, char const & chr) {
    return std::string(str).find(chr) != std::string::npos;
}


void printStack(std::stack<std::string> st) {
    while (!st.empty()) {
        std::cout << '\'' << st.top() << '\'' << std::endl;
        st.pop();
    }
}

template <typename VALUE_TYPE>
bool isKeyExist(std::string const & key, std::map<std::string const, VALUE_TYPE> const & mp) {
    if (mp.find(key) != mp.end())
        return true;
    return false;
}

bool isKeyStartsWithExist(std::string const & keyPart, std::map<std::string const, AbstractOperatorFactory *> const & mp) {
    for (auto iter = mp.begin(); iter != mp.end(); ++iter)
        if (iter->first.find(keyPart) == 0)
            return true;
    return false;
}

void pushLexem(std::stack<std::string> & lexems, std::string & lexem) {
    if (!lexem.empty()) {
        lexems.push(lexem);
        lexem.clear();
    }
}

void pushToLexem(std::string & lexem, char const & symbol) {
    if (symbol != ' ')
        lexem.push_back(symbol);
}

class Parser {
private:
    std::map<std::string const, AbstractOperatorFactory *> operatorMap = {
        {"+", new AdditionOperatorFactory},
        {"-", new SubtractionOperatorFactory},
        {"*", new AdditionOperatorFactory},
        {"**", new AdditionOperatorFactory}
    };

public:
    void parseString(std::string line) {
        std::cout << line << std::endl;
        line.push_back(' ');    // костыль, чтобы сделать один дополнительный шаг в конце
        std::stack<std::string> lexems;
        std::string lexem;
        std::string sublexem;

        std::size_t len = line.length();
        char symbol;

        bool addStatus = false; // addStatus истинен, если стоит произвести донабор лексемы для поиска ее в мапе

        for (std::size_t i = 0; i < len; ++i) {
            symbol = line[i];
            if (!addStatus) {
                if (symbol == ' ') 
                    pushLexem(lexems, lexem);

                else if (isKeyStartsWithExist(std::string(1, symbol), operatorMap)) {
                    pushLexem(lexems, lexem);
                    pushToLexem(lexem, symbol);
                    addStatus = true;
                }

                else
                    pushToLexem(lexem, symbol);
            }
            
            else {
                if (isKeyStartsWithExist(lexem, operatorMap)) {
                    if (isKeyExist(lexem, operatorMap))
                        sublexem = lexem;
                    pushToLexem(lexem, symbol);
                }
                else {
                    lexem = lexem.substr(lexem.length() - 1);   // при переходе в потерянное состояние в лексеме содержится оператор +1 символ, не входящий в оператор (он стоит последним)
                    --i;    // возвращаемся на шаг назад, чтобы не потерять текущий символ после того, который перевел цикл в потерянное состояние
                    pushLexem(lexems, sublexem);
                    addStatus = false;
                }
            }
        }
        lexems.push(lexem);
        lexem.clear();

        lexems.pop();   // убираем лишний пробел в конце, который появился из-за костыля
        printStack(lexems);
    }
};

#endif
