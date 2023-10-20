//#include "IConnection.hpp"
#include <cstddef>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>

#define PAINT_CALCULATION_TABLE_NAME "расчет печатной краски"
#define LACQUER_CALCULATION_TABLE_NAME "расчет лака"

//#include "JsonConnection.hpp"
//#include "calculation_functions.hpp"

#include "IOption.hpp"
#include "BaseOptionContainer.hpp"

int main() {

BaseOptionContainer * rootContainer = new BaseOptionContainer("root container", BASE_HELP_TEXT, true);
	BaseOptionContainer * container1 = new BaseOptionContainer("first container");
	BaseOptionContainer * container2 = new BaseOptionContainer("second container");
	BaseOptionContainer * container3 = new BaseOptionContainer("third container");

	rootContainer->addOption('c', container1);
	container1->addOption('c', container2);
	container2->addOption('c', container3);

	rootContainer->exec(0, std::cin, std::cout, "\n");

	delete rootContainer;

	/*
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

	auto paintPreset = conn->getPreset(PAINT_CALCULATION_TABLE_NAME, 2);
	std::cout << paintPreset << std::endl;
	std::cout << calculatePaintAmount(conn, paintPreset) << std::endl;

	std::cout << std::endl;

	auto lacquerPreset = conn->getPreset(LACQUER_CALCULATION_TABLE_NAME, "1");
	std::cout << lacquerPreset << std::endl;
	std::cout << calculateLacquerAmount(lacquerPreset) << std::endl;

	delete conn;
	*/
}
