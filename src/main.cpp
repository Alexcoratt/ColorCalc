#include <iostream>
#include <vector>
#include <string>

#include "MathParser.hpp"

int main() {
    std::string line = "77 * 7 / 3 + (23.07 * 0.3) -153";
    std::cout << line << std::endl;

    MathParser prs;
    std::cout << prs.parseString(line) << std::endl;

    return 0;
}
