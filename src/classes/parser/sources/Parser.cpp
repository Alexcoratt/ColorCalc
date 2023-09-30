#include <algorithm>

#include "Parser.hpp"

template <typename T>
std::string vectorToString(std::vector<T> const & lines) {
    std::size_t count = lines.size();
    if (count == 0)
        return "()";

    std::string res = "(";
    for (std::size_t i = 1; i < count; ++i) {
        res.append(", ").append(std::to_string(lines[i]));
    }
    return res.append(")");
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
        if (lexem != separator);
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


Parser::Parser() {
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

Parser::Parser(Parser const & other) : _operatorMap(other._operatorMap), _priorityBoostersMap(other._priorityBoostersMap) {}

Parser & Parser::operator=(Parser const & other) {
    if (this != &other) {
        Parser tmp(other);
        swap(tmp);
    }
    return *this;
}

Parser::~Parser() {
    for (auto oper : _operatorMap)
            delete oper.second;
}

void Parser::swap(Parser & other) {
    std::swap(_operatorMap, other._operatorMap);
    std::swap(_priorityBoostersMap, other._priorityBoostersMap);
}

std::string Parser::parseString(std::string const & prompt) {
    std::vector<std::string> lexems = extractLexems(prompt, concatenateVectors(getKeys(_operatorMap), getKeys(_priorityBoostersMap)));

        std::size_t lexemCount = lexems.size();
        std::vector<IExpressionFactory *> factories;
        std::map<std::size_t, int> priorityBoostersPositions;
        std::stack<LeafExpressionFactory *> leaves;

        for (std::size_t i = 0; i < lexemCount; ++i) {
            if (isKeyExist(lexems[i], _operatorMap))
                factories.push_back(_operatorMap[lexems[i]]);

            else if (isKeyExist(lexems[i], _priorityBoostersMap))
                priorityBoostersPositions[factories.size()] = getValue(priorityBoostersPositions, factories.size(), 0) + _priorityBoostersMap[lexems[i]];

            else {
                LeafExpressionFactory * leaf = new LeafExpressionFactory(std::stod(lexems[i]));
                factories.push_back(leaf);
                leaves.push(leaf);
            }
        }

        std::size_t factoryCount = factories.size();
        std::vector<int> priorities(factoryCount);
        int priorityBoost = 0;

        for (std::size_t i = 0; i < factoryCount; ++i) {
            priorityBoost += getValue(priorityBoostersPositions, i, 0);
            priorities[i] = factories[i]->getPriority() + priorityBoost;
        }

        IExpression * exp = evaluate(factories, priorities, 0, factoryCount);
        while (!leaves.empty()) {
            delete leaves.top();
            leaves.pop();
        }

        std::vector<double> result = exp->exec();
        delete exp;
        

        if (result.size() == 1)
            return std::to_string(result[0]);

        return vectorToString(result);
}

IExpression * Parser::evaluate(std::vector<IExpressionFactory *> const & factories, std::vector<int> const & priorities, std::size_t begin, std::size_t end) const {
    if (begin >= end)
        return 0;

    std::size_t pivot = findMinPos(priorities, begin, end);
    return factories[pivot]->build(evaluate(factories, priorities, begin, pivot), evaluate(factories, priorities, pivot + 1, end));
}
