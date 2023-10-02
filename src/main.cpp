#include <iostream>
#include <vector>
#include <string>

#include "MathParser.hpp"
#include "Environment.hpp"

#include "IValue.hpp"
#include "DoubleValue.hpp"
#include "StringValue.hpp"

int main() {
    std::string line = "7 * (var - 25) + var";
    std::cout << line << std::endl;

    Environment * env = new Environment;
    MathParser prs(env);

    IValue * a = new DoubleValue(10);
    env->setVariable("var", a);

    IExpression * exp = prs.parseString(line);

    std::cout << exp->exec()[0] << std::endl;
    a->setDoubleValue(25);
    std::cout << exp->exec()[0] << std::endl;

    delete env;
    delete exp;

    return 0;
}
