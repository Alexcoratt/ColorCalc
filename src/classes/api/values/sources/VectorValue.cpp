#include <algorithm>
#include "VectorValue.hpp"

VectorValue::VectorValue(std::vector<IValue *> const & values) : _values(values) {}
VectorValue::VectorValue(VectorValue const & other) : _values(other._values) {}

VectorValue & VectorValue::operator=(VectorValue const & other) {
    if (this != &other) {
        VectorValue tmp(other);
        swap(tmp);
    }
    return *this;
}

VectorValue::~VectorValue() {}

void VectorValue::swap(VectorValue & other) {
    std::swap(_values, other._values);
}

std::vector<IValue *> VectorValue::getVectorValue() const { return _values; }
void VectorValue::setVectorValue(std::vector<IValue *> const & values) {
    _values = values;
}

void VectorValue::print(std::ostream & out, std::string const & endline) const {
    out << '[';
    std::size_t len = _values.size();

    for (std::size_t i = 0; i < len - 1; ++i)
        _values[0]->print(out, ", ");

    if (len > 0)
        _values[len - 1]->print(out, "");
    out << ']' << std::endl;
}

VectorValue * VectorValue::getClone() const { return new VectorValue(*this); }
