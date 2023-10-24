#include "detail/exceptions.hpp"
#include "json_fwd.hpp"
#include <cstddef>
#include <algorithm>
#include <exception>
#include <ios>
#include <iostream>
#include <fstream>
#include <istream>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <limits>
#include <vector>

#define PAINT_CALCULATION_TABLE_NAME "расчет печатной краски"
#define LACQUER_CALCULATION_TABLE_NAME "расчет лака"

#include "IConnection.hpp"
#include "JsonConnection.hpp"
#include "calculation_functions.hpp"

#include "IOption.hpp"
#include "BaseOptionContainer.hpp"
#include "CustomLeafOption.hpp"

#define PAINT_TYPE_COLUMN_NAME "тип краски"
#define MATERIAL_TYPE_COLUMN_NAME "тип материала"
#define PAINT_CONSUMPTION_COLUMN_NAME "расход краски"

using json_type_error = nlohmann::json_abi_v3_11_2::detail::type_error;

struct DataShuttle {
	IConnection * conn;	// input value
	nlohmann::json data;
};

std::string dump(nlohmann::json const & value) {
	if (value == nlohmann::json::value_t::null)
		return "undefined";
	return value.dump();
}

void writePrintParameters(IOption *, std::istream &, std::ostream & out, std::string const & endline, DataShuttle * shuttle) {
	std::string const presetNameColumnName = shuttle->conn->getColumnsNames(PAINT_CALCULATION_TABLE_NAME)[shuttle->conn->getPresetNameColumnIndex(PAINT_CALCULATION_TABLE_NAME)];

	std::map<std::string const, std::vector<std::string>> specialValues = {
		{presetNameColumnName, shuttle->conn->getPresetsNames(PAINT_CALCULATION_TABLE_NAME)},
		{PAINT_TYPE_COLUMN_NAME, shuttle->conn->getPaintTypes()},
		{MATERIAL_TYPE_COLUMN_NAME, shuttle->conn->getMaterialTypes()}
	};

	out << "Parameters' values:" << endline;
	for (std::string const & column : shuttle->conn->getColumnsNames(PAINT_CALCULATION_TABLE_NAME)) {
		std::string value;
		try {
			auto pair = specialValues.find(column);
			if (pair != specialValues.end())
				value = pair->second[shuttle->data[column]];
			else
				value = dump(shuttle->data[column]);
		} catch (json_type_error const &) {
			value = "undefined";
		}
		out << column << ":\t" << value << endline;
	}
}

std::size_t setType(std::istream & in, std::ostream & out, std::string const & endline, std::string const & category, std::vector<std::string> const & types, nlohmann::json defaultTypeNumJson) {
	out << "Choose required type of " << category << endline << "Available types:" << endline;
	std::size_t len = types.size();
	for (std::size_t i = 0; i < len; ++i)
		out << (i + 1) << '\t' << types[i] << endline;
	out << endline;

	std::size_t defaultTypeNum;
	try {
		defaultTypeNum = defaultTypeNumJson;
		out << "Current type of " << category << " is \"" << types[defaultTypeNum] << "\"" << endline << endline;
	} catch (json_type_error const &) {
		out << "Current type of " << category << " is undefined" << endline << endline;
		defaultTypeNum = 0;
	}

	in.ignore();
	std::string line;
	std::size_t res;
	while (out << "Enter type index (default=\'" << (defaultTypeNum + 1) << "\'): " && std::getline(in, line)) {
		try {
			if (line == "") {
				res = defaultTypeNum;
				break;
			}
			res = std::stoul(line) - 1;
			if (res < len)
				break;
		} catch (std::invalid_argument const &) {}
		out << "Error: There is no option \"" << line << "\"" << endline;
	}

	out << "Type \"" << types[res] << "\" is set" << endline;
	return res;
}

void setPaintType(IOption *, std::istream & in, std::ostream & out, std::string const & endline, DataShuttle * shuttle) {
	std::size_t paintTypeNum = setType(in, out, endline, "paint", shuttle->conn->getPaintTypes(), shuttle->data[PAINT_TYPE_COLUMN_NAME]);
	shuttle->data[PAINT_TYPE_COLUMN_NAME] = paintTypeNum;
	try {
		std::size_t materialTypeNum = shuttle->data[MATERIAL_TYPE_COLUMN_NAME];
		shuttle->data[PAINT_CONSUMPTION_COLUMN_NAME] = shuttle->conn->getPaintConsumption(paintTypeNum, materialTypeNum);
	} catch (std::invalid_argument const &) {
	} catch (json_type_error const &) {}
}

void setMaterialType(IOption *, std::istream & in, std::ostream & out, std::string const & endline, DataShuttle * shuttle) {
	std::size_t materialTypeNum = setType(in, out, endline, "material", shuttle->conn->getMaterialTypes(), shuttle->data[MATERIAL_TYPE_COLUMN_NAME]);
	shuttle->data[MATERIAL_TYPE_COLUMN_NAME] = materialTypeNum;
	try {
		std::size_t paintTypeNum = shuttle->data[PAINT_TYPE_COLUMN_NAME];
		shuttle->data[PAINT_CONSUMPTION_COLUMN_NAME] = shuttle->conn->getPaintConsumption(paintTypeNum, materialTypeNum);
	} catch (std::invalid_argument const &) {
	} catch (json_type_error const &) {}
}

void setPaintConsumption(IOption *, std::istream & in, std::ostream & out, std::string const & endline, DataShuttle * shuttle) {
	nlohmann::json & paintConsumption = shuttle->data[PAINT_CONSUMPTION_COLUMN_NAME];
	bool valueIsDefined = paintConsumption != nlohmann::json::value_t::null;

	out << "Current paint consumption value is " << paintConsumption;
	if (valueIsDefined)
		out << " g/m^2";
	out << endline;

	std::string const prompt = "Enter value g/m^2 (default=" + dump(paintConsumption) + "): ";
	std::string line;
	double res;
	in.ignore();
	while (out << prompt && std::getline(in, line)) {
		try {
			if (line == "") {
				out << "Value " << dump(paintConsumption) << " is set" << endline;
				break;
			}
			res = std::stod(line);
			if (res > 0) {
				paintConsumption = res;
				out << "Value " << res << " is set" << endline;
				shuttle->data[PAINT_TYPE_COLUMN_NAME] = nlohmann::json::value_t::null;
				shuttle->data[MATERIAL_TYPE_COLUMN_NAME] = nlohmann::json::value_t::null;
				break;
			} else
				out << "Value must be greater than zero" << endline;
		} catch (std::invalid_argument const &) {
			out << "\"" << line << "\" is not a number" << endline;
		}
	}
}

void printPaintConsumption(IOption *, std::istream & in, std::ostream & out, std::string const & endline, DataShuttle const * shuttle) {
	try {
		std::size_t const paintTypeNum = shuttle->data[PAINT_TYPE_COLUMN_NAME];
		std::size_t const materialTypeNum = shuttle->data[MATERIAL_TYPE_COLUMN_NAME];

		out << "Paint type is \"" << shuttle->conn->getPaintTypes()[paintTypeNum] << "\"" << endline;
		out << "Material type is \"" << shuttle->conn->getMaterialTypes()[materialTypeNum] << "\"" << endline;

		auto paintConsumption =  shuttle->conn->getPaintConsumption(paintTypeNum, materialTypeNum);
		out << "Paint consumption is " << paintConsumption << endline;
	} catch (json_type_error const &) {
		out << "The paint type or the material type is not set" << endline;
	} catch (std::invalid_argument const & err) {
		out << "Impossible to print using that type of paint and this type of material" << endline;
	}
	std::cout << shuttle->data << std::endl;
}

int main() {

	std::fstream file("../data/paint.json");
	IConnection * conn = new JsonConnection(file);

	//std::cout << conn->getPresetTemplate("расчет печатной краски") << std::endl;

	DataShuttle paintCalculationShuttle;
	paintCalculationShuttle.conn = conn;
	paintCalculationShuttle.data = conn->getPresetTemplate(PAINT_CALCULATION_TABLE_NAME);

	CustomLeafOption<DataShuttle *> writePrintParametersOption(
		"write values of parameters",
		"Print current values of all paint calculation mode parameters",
		writePrintParameters,
		&paintCalculationShuttle
	);

	CustomLeafOption<DataShuttle *> setPaintTypeOption(
		"set paint type",
		"Set type of paint you are going to use",
		setPaintType,
		&paintCalculationShuttle);

	CustomLeafOption<DataShuttle *> setMaterialTypeOption(
		"set material type",
		"Set type of material you are going to use",
		setMaterialType,
		&paintCalculationShuttle);

	CustomLeafOption<DataShuttle *> printPaintConsumptionOption(
		"get paint consumption",
		"Prints paint consumption on the screen using entered paint type and material type",
		printPaintConsumption,
		&paintCalculationShuttle
	);

	CustomLeafOption<DataShuttle *> setPaintConsumptionOption(
		"set paint consumption",
		"Set paint consumption value manually (paint and material type settings clears if a user enters a new value)",
		setPaintConsumption,
		&paintCalculationShuttle
	);

	BaseOptionContainer paintCalculation("paint calculation", "contains options to work with paint calculation data", {
		{'p', &setPaintTypeOption},
		{'m', &setMaterialTypeOption},
		{'c', &setPaintConsumptionOption},
		{'w', &writePrintParametersOption}
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
