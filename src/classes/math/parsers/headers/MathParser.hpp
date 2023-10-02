#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
#include <map>

#include "IExpressionFactory.hpp"
#include "Environment.hpp"

class MathParser {
private:
    Environment * _env;
    std::map<std::string, IExpressionFactory *> _operatorMap;
    std::map<std::string, int const> _priorityBoostersMap;

public:
    MathParser(Environment *);
    MathParser(MathParser const &);
    MathParser & operator=(MathParser const &);
    ~MathParser();

    void swap(MathParser &);
    
    IExpression * parseString(std::string const &);

    IExpression * evaluate(std::vector<IExpressionFactory *> const &, std::vector<int> const &, std::size_t, std::size_t) const;
};

#endif
