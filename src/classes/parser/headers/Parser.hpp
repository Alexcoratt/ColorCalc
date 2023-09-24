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

class Parser {
private:
    std::map<std::string, AbstractOperatorFactory *> operatorMap = {
        {"+", new AdditionOperatorFactory},
        {"-", new SubtractionOperatorFactory}
    };

public:
    void parseString(std::string line) {
        std::cout << line << std::endl;
        std::stack<AbstractOperator *> lexems;
    }
};

#endif
