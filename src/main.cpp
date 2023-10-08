#include <iostream>
#include <vector>
#include <string>

#include "IValue.hpp"
#include "MathParser.hpp"
#include "Environment.hpp"

int main() {
    Environment * env = new Environment;

    MathParser prs(env);
    IExpression * exp;

    std::vector<std::string> const lines = {
        "a = 10",
        "a",
        "rmvar(a)",
        "a",
        "a = 2",
        "b = 2 - a",
        "c = a + b - rmvar(a)",
        "a - 3"
    };

    IValue * result;

    for (std::string const & line : lines) {
        try {
            std::cout << ">>> " << line << std::endl;
            exp = prs.parseString(line);
            result = exp->exec();
            result->print();
            delete exp;
        } catch(std::exception const & e) {
            std::cerr << e.what() << '\n';
        }
    }

    delete env;

    return 0;
}
