#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
#include <vector>
#include <iostream>

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
            std::cout << lexemType << std::endl;

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

class Parser {
public:
    void parseString(std::string line) {
        // std::cout << line << std::endl;
        printVector(extractLexems(line));
    }
};

#endif
