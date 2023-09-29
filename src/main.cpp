#include <iostream>
#include <vector>
#include <string>

#include "Parser.hpp"

int main() {
    std::string line = "(2 - (3 - 1) + 10.2) * 2 / 100";
    std::cout << line << std::endl;

    Parser prs;
    std::cout << prs.parseString(line) << std::endl;

    return 0;
}
