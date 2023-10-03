#include <iostream>
#include <vector>
#include <string>

#include "MathParser.hpp"
#include "Environment.hpp"

#include "IValue.hpp"
#include "DoubleValue.hpp"
#include "StringValue.hpp"

int main() {
    std::string line;

    Environment * env = new Environment;
    MathParser prs(env);

    IExpression * exp;
    
    while (std::getline(std::cin, line)) {
        try {
            exp = prs.parseString(line);
            std::cout << exp->exec()->getDoubleValue() << std::endl;
            delete exp;
        } catch (std::exception & err) {
            std::cerr << err.what() << std::endl;
        }
    }

    delete env;

    return 0;
}
