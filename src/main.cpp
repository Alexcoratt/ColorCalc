#include <iostream>
#include <fstream>
#include <string>

#include "json.hpp"

using json = nlohmann::json;

int main() {
    std::fstream file("../data/paint.json");

    json data = json::parse(file);

    int paintType = 2;
    int materialType = 3;

    json const & values = data["tables"]["paint_consumption"]["keys"][0]["values"];

    for (auto value : values)
    std::cout << value << std::endl;
}
