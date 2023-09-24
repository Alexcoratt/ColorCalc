#include <iostream>
#include <vector>
#include <string>

#include "IExpression.hpp"
#include "NodeExpression.hpp"
#include "LeafExpression.hpp"

#include "AbstractOperator.hpp"
#include "AdditionOperator.hpp"
#include "SubtractionOperator.hpp"

#include "Parser.hpp"

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

int main() {
    std::string line = "1.2+ 2.323 * 5-3** 2";
    Parser prs;
    prs.parseString(line);

    return 0;
}
