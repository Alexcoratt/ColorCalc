#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
#include <vector>
#include <map>

#include "IExpressionFactory.hpp"
#include "LeafExpressionFactory.hpp"

#include "AdditionExpressionFactory.hpp"
#include "SubtractionExpressionFactory.hpp"
#include "MultiplicationExpressionFactory.hpp"
#include "DivisionExpressionFactory.hpp"

class MathParser {
private:

    std::map<std::string, IExpressionFactory *> _operatorMap;

    std::map<std::string, int const> _priorityBoostersMap;

public:
    MathParser();
    MathParser(MathParser const &);
    MathParser & operator=(MathParser const &);
    ~MathParser();

    void swap(MathParser &);
    
    std::string parseString(std::string const &);

    IExpression * evaluate(std::vector<IExpressionFactory *> const &, std::vector<int> const &, std::size_t, std::size_t) const;
};

#endif
