#include <iostream>
#include <vector>
#include <string>

#include "Parser.hpp"

int main() {
    std::string line = "(2 - (3 - 1) + 10.2) * 2 / 100";
    std::cout << line << std::endl;

    Parser prs;
    prs.parseString(line);

    return 0;
}
