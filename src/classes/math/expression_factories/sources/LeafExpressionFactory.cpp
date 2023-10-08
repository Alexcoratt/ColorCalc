#include <algorithm>
#include <stdexcept>

#include "IExpression.hpp"
#include "ValueExpression.hpp"
#include "LeafExpressionFactory.hpp"
#include "StringValue.hpp"
#include "DoubleValue.hpp"
#include "VariableExpression.hpp"

LeafExpressionFactory::LeafExpressionFactory(Environment * env, std::string const & value) : _env(env), _lexem(value) {}
LeafExpressionFactory::LeafExpressionFactory(LeafExpressionFactory const & other) : _env(other._env), _lexem(other._lexem) {}

LeafExpressionFactory & LeafExpressionFactory::operator=(LeafExpressionFactory const & other) {
    if (this != &other) {
        LeafExpressionFactory tmp(other);
        swap(tmp);
    }
    return *this;
}

LeafExpressionFactory::~LeafExpressionFactory() {}

void LeafExpressionFactory::swap(LeafExpressionFactory & other) {
    std::swap(_env, other._env);
    std::swap(_lexem, other._lexem);
}

IExpression * LeafExpressionFactory::build(IExpression * left, IExpression * right) const {
    IValue * value;

    try {
        return new ValueExpression(new DoubleValue(std::stod(_lexem)));
    } catch (std::invalid_argument const & e) {
        if (_lexem[0] == '\"')
            return new ValueExpression(new StringValue(_lexem));
        return new VariableExpression(_lexem, _env);
    }
}
