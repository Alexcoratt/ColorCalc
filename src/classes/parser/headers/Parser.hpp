#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
#include <vector>
#include <stack>
#include <iostream>
#include <map>

#include <cctype>

#include "IExpressionFactory.hpp"
#include "AdditionExpressionFactory.hpp"

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

template <typename VALUE_TYPE>
bool isKeyStartsWithExist(std::string const & keyPart, std::map<std::string const, VALUE_TYPE> const & mp) {
    for (auto iter = mp.begin(); iter != mp.end(); ++iter)
        if (iter->first.find(keyPart) == 0)
            return true;
    return false;
}

class Parser {
private:

    std::map<std::string const, std::pair<IExpressionFactory *, int>> _operatorMap = {
        {"+", std::pair<IExpressionFactory *, int>(new AdditionExpressionFactory, 0)}
    };

public:
    

    void parseString(std::string line) {
        printVector(extractLexems(line));
    }

    std::vector<std::string> extractLexems(std::string line) {
        std::vector<std::string> lexems;
        std::size_t left = 0;
        std::size_t lineLen = line.length();

        for (std::size_t i = 0; i < lineLen; ++i) {
            if (line[i] == ' ') {
                if (i - left > 0)
                    lexems.push_back(line.substr(left, i - left));
                left = i + 1;
            }

            else if (isKeyStartsWithExist(std::string(1, line[i]), _operatorMap)) {
                if (i - left > 0)
                    lexems.push_back(line.substr(left, i - left));
                left = i;
                std::size_t lexemLen = 1;

                for (std::size_t j = 2; j < lineLen - i; ++j) {
                    if (isKeyExist(line.substr(i, j), _operatorMap))
                        lexemLen = j;
                    else if (!isKeyStartsWithExist(line.substr(i, j - 1), _operatorMap))
                        break;
                }

                lexems.push_back(line.substr(left, lexemLen));
                left += lexemLen;
                i += lexemLen - 1;
            }
        }
        lexems.push_back(line.substr(left));

        return lexems;
    }
};

#endif
