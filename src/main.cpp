//#include "IConnection.hpp"
#include "IConnection.hpp"
#include <cstddef>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <istream>
#include <ostream>
#include <string>

#define PAINT_CALCULATION_TABLE_NAME "расчет печатной краски"
#define LACQUER_CALCULATION_TABLE_NAME "расчет лака"

#include "JsonConnection.hpp"
#include "calculation_functions.hpp"

#include "IOption.hpp"
#include "BaseOptionContainer.hpp"
#include "CustomLeafOption.hpp"

void printPaintTypes(IConnection * conn) {
	auto paintTypes = conn->getPaintTypes();
	for (auto type : paintTypes)
		std::cout << type << std::endl;
}

void printMaterialTypes(IConnection * conn) {
	auto materialTypes = conn->getMaterialTypes();
	for (auto type : materialTypes)
		std::cout << type << std::endl;
}

int main() {

	std::fstream file("../data/paint.json");

	IConnection * conn = new JsonConnection(file);

	BaseOptionContainer root("root", BASE_HELP_TEXT, {
		{'p', new CustomLeafOption<IConnection *>("print paint types", "prints available paint types", printPaintTypes, conn)},
		{'m', new CustomLeafOption<IConnection *>("print material types", "prints available material types", printMaterialTypes, conn)}
	});
	root.getOption('p')->setNoDelete(false);
	root.getOption('m')->setNoDelete(false);

	root.exec(0, std::cin, std::cout, "\n");

	/*
	auto paintType = "фолиевая";
	auto materialType = "невпитывающие материалы";

	std::cout << conn->getPaintConsumption(paintType, materialType) << std::endl << std::endl;

	auto presetsNames = conn->getPresetsNames(PAINT_CALCULATION_TABLE_NAME);
	for (auto name : presetsNames)
		std::cout << name << std::endl;

	auto paintPreset = conn->getPreset(PAINT_CALCULATION_TABLE_NAME, 2);
	std::cout << paintPreset << std::endl;
	std::cout << calculatePaintAmount(conn, paintPreset) << std::endl;

	std::cout << std::endl;

	auto lacquerPreset = conn->getPreset(LACQUER_CALCULATION_TABLE_NAME, "1");
	std::cout << lacquerPreset << std::endl;
	std::cout << calculateLacquerAmount(lacquerPreset) << std::endl;
	*/

	delete conn;

	return 0;
}
