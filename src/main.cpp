#include "IConnection.hpp"
#include "classes/headers/IConnection.hpp"
#include "cli/leaf_options/headers/CustomLeafOption.hpp"
#include "cli/leaf_options/headers/IOption.hpp"
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

struct PaintMaterialBus {
	IConnection * conn;			// input value
	std::size_t paintTypeNum = 0;	// output value
	std::size_t materialTypeNum = 0;	// output value
};

void setPaintType(IOption *, std::istream & in, std::ostream & out, std::string const & endline, PaintMaterialBus * bus) {
	auto paintTypes = bus->conn->getPaintTypes();
	std::size_t len = paintTypes.size();

	out << "Choose required type of paint" << endline << "Available types:" << endline;
	for (std::size_t i = 1; i <= len; ++i)
		out << i << '\t' << paintTypes[i - 1] << endline;
	out << endline;

	out << "Enter type index: ";
	in >> bus->paintTypeNum;
	while (bus->paintTypeNum > len && !in.eof()) {
		out << "There is no such option" << endline;
		out << "Enter type index: ";
		in >> bus->paintTypeNum;
	}

	if (!in.eof()) {
		bus->paintTypeNum--;
		out << "Type \"" << paintTypes[bus->paintTypeNum] << "\" is set" << endline;
	}
}

void setMaterialType(IOption *, std::istream & in, std::ostream & out, std::string const & endline, PaintMaterialBus * bus) {
	auto materialTypes = bus->conn->getMaterialTypes();
	std::size_t len = materialTypes.size();

	out << "Choose required type of material" << endline << "Available types:" << endline;
	for (std::size_t i = 1; i <= len; ++i)
		out << i << '\t' << materialTypes[i - 1] << endline;
	out << endline;

	out << "Enter type index: ";
	in >> bus->materialTypeNum;
	while (bus->materialTypeNum > len && !in.eof()) {
		out << "There is no such option" << endline;
		out << "Enter type index: ";
		in >> bus->materialTypeNum;
	}

	if (!in.eof()) {
		bus->materialTypeNum--;
		out << "Type \"" << materialTypes[bus->materialTypeNum] << "\" is set" << endline;
	}
}

void printPaintConsumption(IOption *, std::istream & in, std::ostream & out, std::string const & endline, PaintMaterialBus const * bus) {
	out << "Paint type is \"" << bus->conn->getPaintTypes()[bus->paintTypeNum] << "\"" << endline;
	out << "Material type is \"" << bus->conn->getMaterialTypes()[bus->materialTypeNum] << "\"" << endline;

	try {
		auto paintConsumption =  bus->conn->getPaintConsumption(bus->paintTypeNum, bus->materialTypeNum);
		out << "Paint consumption is " << paintConsumption << endline;
	} catch (std::invalid_argument const & err) {
		out << "Impossible to print using that type of paint and this type of material" << endline;
	}
}

int main() {

	std::fstream file("../data/paint.json");
	IConnection * conn = new JsonConnection(file);

	PaintMaterialBus paintMaterialBus;
	paintMaterialBus.conn = conn;

	CustomLeafOption<PaintMaterialBus *> setPaintTypeOption(
		"set paint type",
		"Set type of paint you are going to use",
		setPaintType,
		&paintMaterialBus);

	CustomLeafOption<PaintMaterialBus *> setMaterialTypeOption(
		"set material type",
		"Set type of material you are going to use",
		setMaterialType,
		&paintMaterialBus);

	CustomLeafOption<PaintMaterialBus *> printPaintConsumptionOption(
		"get paint consumption",
		"Prints paint consumption on the screen using entered paint type and material type",
		printPaintConsumption,
		&paintMaterialBus
	);

	BaseOptionContainer paintCalculation("paint calculation", "contains options to work with paint calculation data", {
		{'p', &setPaintTypeOption},
		{'m', &setMaterialTypeOption},
		{'c', &printPaintConsumptionOption}
	});

	BaseOptionContainer root("root", BASE_HELP_TEXT, {
		{'p', &paintCalculation}
	}, true);
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
