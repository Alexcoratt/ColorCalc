#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
#include <vector>
#include <stack>
#include <iostream>
#include <map>

#include <cctype>

#include "IExpressionFactory.hpp"
#include "LeafExpressionFactory.hpp"

#include "AdditionExpressionFactory.hpp"
#include "SubtractionExpressionFactory.hpp"
#include "MultiplicationExpressionFactory.hpp"
#include "DivisionExpressionFactory.hpp"

template <typename T>
void printVector(std::vector<T> const & lines) {
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

template <typename T>
void printStack(std::stack<T> const & st) {
    for (auto elem : st)
        std::cout << '\'' << elem << '\'' << std::endl;
}

template <typename VALUE_TYPE>
bool isKeyExist(std::string const & key, std::map<std::string const, VALUE_TYPE> const & mp) {
    return mp.find(key) != mp.end();
}


template <typename VALUE_TYPE>
bool isKeyStartsWithExist(std::string const & keyPart, std::map<std::string const, VALUE_TYPE> const & mp) {
    for (auto iter = mp.begin(); iter != mp.end(); ++iter)
        if (iter->first.find(keyPart) == 0)
            return true;
    return false;
}

template <typename VALUE_TYPE>
bool isKeyStartsWithExist(char keyPart, std::map<std::string const, VALUE_TYPE> const & mp) {
    for (auto iter = mp.begin(); iter != mp.end(); ++iter)
        if (iter->first[0] == keyPart)
            return true;
    return false;
}


template <typename KEY_TYPE, typename VALUE_TYPE>
VALUE_TYPE getValue(std::map<KEY_TYPE, VALUE_TYPE> map, KEY_TYPE key, VALUE_TYPE defaultValue) {
    if (map.find(key) != map.end())
        return map[key];
    return defaultValue;
}

std::size_t findMinPos(std::vector<int> const & values, std::size_t begin, std::size_t end) {
    std::size_t pos = end - 1;
    int min = values[pos];
    for (std::size_t i = end - 1; i > begin; --i) {
        if (min >= values[i - 1]) {
            pos = i - 1;
            min = values[i - 1];
        }
    }
    return pos;
}

class Parser {
private:

    std::map<std::string const, IExpressionFactory *> _operatorMap = {
        {"+", new AdditionExpressionFactory},
        {"-", new SubtractionExpressionFactory},
        {"*", new MultiplicationExpressionFactory},
        {"/", new DivisionExpressionFactory}
    };

    std::map<std::string const, int const> _priorityBoostersMap = {
        {"(", 6},
        {")", -6}
    };

public:
    
    void parseString(std::string line) {
        std::vector<std::string> lexems = extractLexems(line);

        std::size_t lexemCount = lexems.size();
        std::vector<IExpressionFactory *> factories;
        std::map<std::size_t, int> priorityBoostersPositions;

        for (std::size_t i = 0; i < lexemCount; ++i) {
            if (isKeyExist(lexems[i], _operatorMap))
                factories.push_back(_operatorMap[lexems[i]]);

            else if (isKeyExist(lexems[i], _priorityBoostersMap))
                priorityBoostersPositions[factories.size()] = getValue(priorityBoostersPositions, factories.size(), 0) + _priorityBoostersMap[lexems[i]];

            else
                factories.push_back(new LeafExpressionFactory(std::stod(lexems[i])));
        }

        std::size_t factoryCount = factories.size();
        std::vector<int> priorities(factoryCount);
        int priorityBoost = 0;

        for (std::size_t i = 0; i < factoryCount; ++i) {
            priorityBoost += getValue(priorityBoostersPositions, i, 0);
            priorities[i] = factories[i]->getPriority() + priorityBoost;
        }

        printVector(lexems);
        printVector(priorities);

        IExpression * exp = evaluate(factories, priorities, 0, factoryCount);
        printVector(exp->exec());
    }

    IExpression * evaluate(std::vector<IExpressionFactory *> const & factories, std::vector<int> const & priorities, std::size_t begin, std::size_t end) {
        if (begin >= end)
            return 0;

        std::size_t pivot = findMinPos(priorities, begin, end);
        //std::cout << pivot << ' ' <<  begin << ' ' << end << std::endl;
        return factories[pivot]->build(evaluate(factories, priorities, begin, pivot), evaluate(factories, priorities, pivot + 1, end));
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

            else if (isKeyStartsWithExist(line[i], _operatorMap) || isKeyStartsWithExist(line[i], _priorityBoostersMap)) {
                if (i - left > 0)
                    lexems.push_back(line.substr(left, i - left));
                left = i;
                std::size_t lexemLen = 1;

                for (std::size_t j = 2; j < lineLen - i; ++j) {
                    if (isKeyExist(line.substr(i, j), _operatorMap) || isKeyExist(line.substr(i, j), _priorityBoostersMap))
                        lexemLen = j;
                    else if (!isKeyStartsWithExist(line.substr(i, j - 1), _operatorMap) && !isKeyStartsWithExist(line.substr(i, j - 1), _priorityBoostersMap))
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
