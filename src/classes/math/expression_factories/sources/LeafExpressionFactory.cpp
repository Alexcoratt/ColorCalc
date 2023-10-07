#include <algorithm>
#include <stdexcept>

#include "LeafExpressionFactory.hpp"
#include "StringValue.hpp"

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

LeafExpression * LeafExpressionFactory::build(IExpression * left, IExpression * right) const {
    IValue * value;
    bool isVariable = false;

    try {
        value = new DoubleValue(std::stod(_lexem));
    } catch (std::invalid_argument const & e) {
        if (_env->containsVariable(_lexem)) {
            value = _env->getValue(_lexem);
            isVariable = true;
        } else
            value = new StringValue(_lexem);
    }

    return new LeafExpression(value, isVariable);
}
