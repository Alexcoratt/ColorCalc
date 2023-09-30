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

class Parser {
private:

    std::map<std::string, IExpressionFactory *> _operatorMap;

    std::map<std::string, int const> _priorityBoostersMap;

public:
    Parser();
    Parser(Parser const &);
    Parser & operator=(Parser const &);
    ~Parser();

    void swap(Parser &);
    
    std::string parseString(std::string const &);

    IExpression * evaluate(std::vector<IExpressionFactory *> const &, std::vector<int> const &, std::size_t, std::size_t) const;
};

#endif
