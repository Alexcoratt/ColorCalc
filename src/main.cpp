#include <iostream>
#include <vector>
#include <string>

#include "MathParser.hpp"
#include "Environment.hpp"

#include "IValue.hpp"
#include "DoubleValue.hpp"
#include "StringValue.hpp"

#include "CommandParser.hpp"

int main() {
    std::string line;

    Environment * env = new Environment;
    CommandParser prs(env);
    
    while (std::getline(std::cin, line)) {
        try {
            prs.parseString(line);
        } catch (std::exception & err) {
            std::cerr << err.what() << std::endl;
        }
    }

    delete env;

    return 0;
}
