#include <iostream>
#include <vector>
#include <string>

#include "MathParser.hpp"
#include "Environment.hpp"
#include "DoubleValue.hpp"

int main() {
    std::string line = "77 * b";
    std::cout << line << std::endl;

    Environment * env = new Environment;
    MathParser prs(env);

    DoubleValue * a = new DoubleValue(10);
    env->setVariable("a", a);

    std::cout << prs.parseString(line) << std::endl;

    return 0;
}
