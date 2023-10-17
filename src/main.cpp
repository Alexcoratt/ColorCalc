#include <cstddef>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>

#define PAINT_CALCULATION_TABLE_NAME "расчет печатной краски"

#include "JsonConnection.hpp"

int main() {
	std::fstream file("../data/paint.json");

	IConnection * conn = new JsonConnection(file);

	auto paintType = "фолиевая";
	auto materialType = "невпитывающие материалы";

	auto paintTypes = conn->getPaintTypes();
	for (auto type : paintTypes)
		std::cout << type << std::endl;

	std::cout << std::endl;

	auto materialTypes = conn->getMaterialTypes(paintType);
	for (auto type : materialTypes)
		std::cout << type << std::endl;

	std::cout << std::endl;

	std::cout << conn->getPaintConsumption(paintType, materialType) << std::endl << std::endl;

	auto presetsNames = conn->getPresetsNames(PAINT_CALCULATION_TABLE_NAME);
	for (auto name : presetsNames)
		std::cout << name << std::endl;

	std::cout << conn->getPreset(PAINT_CALCULATION_TABLE_NAME, "Многокрасочная печать") << std::endl;

	delete conn;
}
