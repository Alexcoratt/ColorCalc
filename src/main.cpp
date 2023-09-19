#include <iostream>
#include <vector>
#include <string>

#include "IExpression.hpp"
#include "NodeExpression.hpp"
#include "LeafExpression.hpp"

#include "IOperator.hpp"
#include "AdditionOperator.hpp"
#include "SubtractionOperator.hpp"

std::vector<std::string> split(std::string line, std::string delimiter = " ") {
    std::vector<std::string> res;
    std::string sub;
    std::size_t left = 0, right = 0;

    while ( (right = line.find(delimiter, left)) != std::string::npos ) {
        sub = line.substr(left, right - left);
        if (sub.length() > 0)
            res.push_back(sub);
        left = right + delimiter.length();
    }

    sub = line.substr(left);
    if (sub.length() > 0)
        res.push_back(sub);

    return res;
}

template <typename T>
void printVector(std::vector<T> lines) {
    std::size_t count = lines.size();
    std::cout << '[' << lines[0];
    for (std::size_t i = 1; i < count; ++i) {
        std::cout << ", " << lines[i];
    }
    std::cout << ']' << std::endl;
}


int main() {
    IExpression * a = new LeafExpression(1);
    IExpression * b = new LeafExpression(-2);

    IOperator * plus = new AdditionOperator();
    IOperator * minus = new SubtractionOperator();

    IExpression * c = new NodeExpression(minus, {a, b});

    IExpression * d = new LeafExpression(10);
    IExpression * e = new NodeExpression(plus, {d, c});

    std::cout << e->calculate() << std::endl;

    return 0;
}
