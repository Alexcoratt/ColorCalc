#include <iostream>
#include <vector>
#include <string>

#include "IExpression.hpp"
#include "LeafExpression.hpp"

#include "Parser.hpp"

int main() {
    std::string line = "1.2+ 2.323 + 2";
    Parser prs;
    prs.parseString(line);

    return 0;
}
