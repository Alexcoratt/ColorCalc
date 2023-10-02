#include <algorithm>
#include <stdexcept>

#include "LeafExpressionFactory.hpp"
#include "ValueException.hpp"

LeafExpressionFactory::LeafExpressionFactory(Environment * env, std::string const & value) : _env(env), _value(value) {}
LeafExpressionFactory::LeafExpressionFactory(LeafExpressionFactory const & other) : _env(other._env), _value(other._value) {}

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
    std::swap(_value, other._value);
}

LeafExpression * LeafExpressionFactory::build(IExpression * left, IExpression * right) const {
    DoubleValue * value;
    bool isVariable = true;
    try {
        value = new DoubleValue(std::stod(_value));
        isVariable = false;
    } catch (std::invalid_argument const & e) {
        if ( !(value = dynamic_cast<DoubleValue *>(_env->getValue(_value))) )
            throw ValueException("Value exception: type of value for a leaf expression must be double");
    }
    return new LeafExpression(value, isVariable);
}

int LeafExpressionFactory::getPriority() const { return 4; }