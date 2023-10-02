#include <algorithm>
#include <string>
#include <stack>

#include <iostream>

#include "MathParser.hpp"

#include "IExpressionFactory.hpp"
#include "AdditionExpressionFactory.hpp"
#include "SubtractionExpressionFactory.hpp"
#include "MultiplicationExpressionFactory.hpp"
#include "DivisionExpressionFactory.hpp"
#include "LeafExpressionFactory.hpp"

#include "Environment.hpp"

template <typename T>
std::string vectorToString(std::vector<T> const & lines) {
    std::size_t count = lines.size();
    if (count == 0)
        return "()";

    std::string res = "(" + std::to_string(lines[0]);
    for (std::size_t i = 1; i < count; ++i) {
        res.append(", ").append(std::to_string(lines[i]));
    }
    return res.append(")");
}

std::string vectorToString(std::vector<std::string> const & lines) {
    std::size_t count = lines.size();
    if (count == 0)
        return "()";

    std::string res = "(\"" + lines[0];
    for (std::size_t i = 1; i < count; ++i) {
        res.append("\", \"").append(lines[i]);
    }
    return res.append("\")");
}

template <typename KEY_TYPE, typename VALUE_TYPE>
bool isKeyExist(KEY_TYPE key, std::map<KEY_TYPE, VALUE_TYPE> const & mp) {
    return mp.find(key) != mp.end();
}

template <typename KEY_TYPE, typename VALUE_TYPE>
VALUE_TYPE getValue(std::map<KEY_TYPE, VALUE_TYPE> map, KEY_TYPE key, VALUE_TYPE defaultValue) {
    if (map.find(key) != map.end())
        return map[key];
    return defaultValue;
}


std::size_t findMinPos(std::vector<int> const & values, std::size_t begin, std::size_t end) {
    std::size_t pos = begin;
    int min = values[begin];
    for (std::size_t i = begin + 1; i < end; ++i) {
        if (min >= values[i]) {
            pos = i;
            min = values[i];
        }
    }
    return pos;
}


template <typename T>
bool isInVector(T toFind, std::vector<T> vect) {
    for (T elem : vect)
        if (elem == toFind)
            return true;
    return false;
}

bool hasElemStartsWith(std::string start, std::vector<std::string> vect) {
    for (std::string elem : vect)
        if (elem.find(start) == 0)
            return true;
    return false;
}

bool hasElemStartsWith(char start, std::vector<std::string> vect) {
    for (std::string elem : vect)
        if (elem[0] == start)
            return true;
    return false;
}

std::vector<std::string> extractLexems(std::string const & prompt, std::vector<std::string> knownLexems, std::string const & separator = " ") {
    std::vector<std::string> lexems;
        std::size_t left = 0;
        std::size_t promptLen = prompt.length();

        knownLexems.push_back(separator);
        std::string lexem;

        for (std::size_t i = 0; i < promptLen; ++i) {
            if (hasElemStartsWith(prompt[i], knownLexems)) {
                if (i - left > 0)
                    lexems.push_back(prompt.substr(left, i - left));
                left = i;
                std::size_t lexemLen = 1;

                for (std::size_t j = 2; j < promptLen - i; ++j) {
                    if (isInVector(prompt.substr(i, j), knownLexems))
                        lexemLen = j;
                    else if (!hasElemStartsWith(prompt.substr(i, j - 1), knownLexems))
                        break;
                }
                
                lexem = prompt.substr(left, lexemLen);

                if (lexem != separator)
                    lexems.push_back(lexem);

                left += lexemLen;
                i += lexemLen - 1;
            }
        }

        lexem = prompt.substr(left);
        if (lexem != separator && lexem.size() > 0)
            lexems.push_back(lexem);

        return lexems;
}

template <typename KEY_TYPE, typename VALUE_TYPE>
std::vector<KEY_TYPE> getKeys(std::map<KEY_TYPE, VALUE_TYPE> const & mp) {
    std::vector<KEY_TYPE> res;
    for (auto iter = mp.begin(); iter != mp.end(); ++iter) {
        res.push_back(iter->first);
    }
    return res;
}

template <typename T>
std::vector<T> concatenateVectors(std::vector<T> left, std::vector<T> right) {
    std::vector<T> res;
    res.reserve(left.size() + right.size());
    res.insert(res.end(), left.begin(), left.end());
    res.insert(res.end(), right.begin(), right.end());
    return res;
}


MathParser::MathParser(Environment * env) : _env(env) {
    _operatorMap = {
        {"+", new AdditionExpressionFactory},
        {"-", new SubtractionExpressionFactory},
        {"*", new MultiplicationExpressionFactory},
        {"/", new DivisionExpressionFactory}
    };

    _priorityBoostersMap = {
        {"(", 6},
        {")", -6}
    };
}

MathParser::MathParser(MathParser const & other) : _env(other._env), _operatorMap(other._operatorMap), _priorityBoostersMap(other._priorityBoostersMap) {}

MathParser & MathParser::operator=(MathParser const & other) {
    if (this != &other) {
        MathParser tmp(other);
        swap(tmp);
    }
    return *this;
}

MathParser::~MathParser() {
    for (auto oper : _operatorMap)
            delete oper.second;
}

void MathParser::swap(MathParser & other) {
    std::swap(_operatorMap, other._operatorMap);
    std::swap(_priorityBoostersMap, other._priorityBoostersMap);
}

IExpression * MathParser::parseString(std::string const & prompt) {
    std::vector<std::string> lexems = extractLexems(prompt, concatenateVectors(getKeys(_operatorMap), getKeys(_priorityBoostersMap)));

    std::size_t lexemCount = lexems.size();
    std::vector<IExpressionFactory *> factories;
    std::stack<LeafExpressionFactory *> leaves;

    std::vector<int> priorities;
    int priorityBoost = 0;

    for (std::size_t i = 0; i < lexemCount; ++i) {
        if (isKeyExist(lexems[i], _operatorMap)) {
            factories.push_back(_operatorMap[lexems[i]]);
            priorities.push_back(_operatorMap[lexems[i]]->getPriority() + priorityBoost);
        }

        else if (isKeyExist(lexems[i], _priorityBoostersMap))
            priorityBoost += _priorityBoostersMap[lexems[i]];

        else {
            LeafExpressionFactory * leaf = new LeafExpressionFactory(_env, lexems[i]);
            factories.push_back(leaf);
            leaves.push(leaf);
            priorities.push_back(leaf->getPriority() + priorityBoost);
        }
    }

    if (priorityBoost != 0)
        std::cerr << "WARNING: The expression has an unclosed parentheses or another expression priority boosting operator" << std::endl;

    IExpression * exp = evaluate(factories, priorities, 0, factories.size());
    while (!leaves.empty()) {
        delete leaves.top();
        leaves.pop();
    }

    return exp;
    /*
    std::vector<double> result = exp->exec();
    delete exp;
    

    if (result.size() == 1)
        return std::to_string(result[0]);

    return vectorToString(result);
    */
}

IExpression * MathParser::evaluate(std::vector<IExpressionFactory *> const & factories, std::vector<int> const & priorities, std::size_t begin, std::size_t end) const {
    if (begin >= end)
        return 0;

    std::size_t pivot = findMinPos(priorities, begin, end);
    return factories[pivot]->build(evaluate(factories, priorities, begin, pivot), evaluate(factories, priorities, pivot + 1, end));
}
