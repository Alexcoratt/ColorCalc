#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <stack>

#include <cctype>

#define DIGIT_TYPE 0
#define ALPHA_TYPE 1
#define OPERATOR_TYPE 2
#define SPACE_TYPE 3
#define DOT_TYPE 4
#define BRACKET_TYPE 5

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

std::map<std::string, int> priorityMap({
    {"+", 0},
    {"-", 0},
    {"*", 1},
    {"/", 1},
    {"**", 2}
});

class Parser {
public:
    void parseString(std::string line) {
        std::cout << line << std::endl;
    }
};

#endif
