#include <algorithm>
#include <stdexcept>

#include "LeafExpressionFactory.hpp"

LeafExpressionFactory::LeafExpressionFactory(Environment * env, std::string const & value) {
    try {
        _value = std::stod(value);
    } catch (std::invalid_argument const & e) {
        _value = env->getValue(value)->getDoubleValue();
    }
}
LeafExpressionFactory::LeafExpressionFactory(LeafExpressionFactory const & other) : _value(other._value) {}

LeafExpressionFactory & LeafExpressionFactory::operator=(LeafExpressionFactory const & other) {
    if (this != &other) {
        LeafExpressionFactory tmp(other);
        swap(tmp);
    }
    return *this;
}

LeafExpressionFactory::~LeafExpressionFactory() {}

void LeafExpressionFactory::swap(LeafExpressionFactory & other) {
    std::swap(_value, other._value);
}

LeafExpression * LeafExpressionFactory::build(IExpression * left, IExpression * right) const {
    return new LeafExpression(_value);
}

int LeafExpressionFactory::getPriority() const { return 4; }