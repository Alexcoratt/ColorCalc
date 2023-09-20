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
        // std::cout << line << std::endl;
        std::vector<std::string> lexems = extractLexems(line);
        printVector(lexems);
        std::cout << bracketsCheck(lexems) << std::endl;
        std::cout << findLessPriorityOperator(lexems) << std::endl;
    }

    int defineSymbolType(char symbol) {
        if (stringContainsChar("\t ", symbol))
            return SPACE_TYPE;

        else if (symbol == '.')
            return DOT_TYPE;

        else if (std::isdigit(symbol))
            return DIGIT_TYPE;

        else if (stringContainsChar("+-*/^", symbol))
            return OPERATOR_TYPE;

        else if (stringContainsChar("()[]{}", symbol))
            return BRACKET_TYPE;

        return ALPHA_TYPE;
    }

    std::vector<std::string> extractLexems(std::string line) {
        std::vector<std::string> lexems;
        std::string lexem;
        int lexemType;

        for (char & symbol : line) {
            if (lexem.length() == 0)
                lexemType = defineSymbolType(symbol);

            switch (defineSymbolType(symbol)) {
                case SPACE_TYPE:
                    if (lexem.length() > 0) {
                        lexems.push_back(lexem);
                        lexem.clear();
                    }
                    break;

                case DOT_TYPE:
                    if (lexemType != DIGIT_TYPE) {
                        if (lexem.length() > 0) {
                            lexems.push_back(lexem);
                            lexem.clear();
                        }
                        lexems.push_back(std::string(1, symbol));
                    }
                    else
                        lexem.push_back(symbol);
                    break;

                case BRACKET_TYPE:
                    if (lexem.length() > 0) {
                        lexems.push_back(lexem);
                        lexem.clear();
                    }
                    lexems.push_back(std::string(1, symbol));
                    break;
                
                default:
                    int currentType = defineSymbolType(symbol);
                    if (currentType == lexemType)
                        lexem.push_back(symbol);
                    else {
                        lexems.push_back(lexem);
                        lexem.clear();
                        lexem.push_back(symbol);
                        lexemType = currentType;
                    }
                    break;
            }                
        }
        
        if (lexem.length() > 0)
            lexems.push_back(lexem);

        return lexems;
    }

    std::size_t findLessPriorityOperator(std::vector<std::string> const & lexems) {
        std::size_t res = lexems.size();   
        int maxPriority = 3;   // replace with max priority (+ 1) found inside priorityMap
        for (std::size_t i = lexems.size(); i > 0; --i) {
            auto search = priorityMap.find(lexems[i - 1]);
            if (search != priorityMap.end()) {
                if (maxPriority > search->second) {
                    res = i - 1;
                    maxPriority = search->second;
                }
            }

            if (std::string(")]}").find(lexems[i - 1]) != std::string::npos) {
                std::stack<std::string> brackets;
                brackets.push(lexems[i - 1]);

                while (!brackets.empty() && --i > 0) {
                    if (std::string(")]}").find(lexems[i - 1]) != std::string::npos)
                        brackets.push(lexems[i - 1]);
                    std::vector<std::string> pairs({"()", "[]", "{}"});
                    for (std::string pair : pairs)
                        if (lexems[i - 1] == pair.substr(0, 1) && brackets.top() == pair.substr(1, 2))
                            brackets.pop();
                }
            }
        }
        return res;
    }

    bool bracketsCheck(std::vector<std::string> const & lexems) {
        std::stack<std::string> brackets;
        for (std::size_t i = 0; i < lexems.size(); ++i) {
            if (std::string("([{").find(lexems[i]) != std::string::npos)
                brackets.push(lexems[i]);
            std::vector<std::string> pairs({"()", "[]", "{}"});
            for (std::string pair : pairs)
                if (lexems[i] == pair.substr(1, 2) && brackets.top() == pair.substr(0, 1))
                    brackets.pop();
        }
        return brackets.empty();
    }
};

#endif
