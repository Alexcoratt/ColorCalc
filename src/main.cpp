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

    std::cout << prs.parseString(line) << std::endl;

    return 0;
}
