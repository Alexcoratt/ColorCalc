#include "detail/exceptions.hpp"
#include "json_fwd.hpp"
#include <cstddef>
#include <algorithm>
#include <exception>
#include <functional>
#include <ios>
#include <iostream>
#include <fstream>
#include <istream>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <limits>
#include <sys/types.h>
#include <vector>

#include "IConnection.hpp"
#include "JsonConnection.hpp"
#include "calculation_functions.hpp"
#include "PaintDataContainer.hpp"

#include "IOption.hpp"
#include "BaseOptionContainer.hpp"
#include "CustomLeafOption.hpp"

#include "JsonValueIsNullException.hpp"
#include "DefaultOptionIsChosenExcepion.hpp"

#define PAINT_TYPE_COLUMN_NAME "тип краски"
#define MATERIAL_TYPE_COLUMN_NAME "тип материала"
#define PAINT_CONSUMPTION_COLUMN_NAME "расход краски"

#define PAINT_CALCULATION_TABLE_NAME "расчет печатной краски"
#define LACQUER_CALCULATION_TABLE_NAME "расчет лака"

using json_type_error = nlohmann::json_abi_v3_11_2::detail::type_error;

std::string dump(nlohmann::json const & value, bool useQuotations = false) {
	if (value == nlohmann::json::value_t::null)
		return "undefined";
	if (useQuotations)
		return "\"" + value.dump() + "\"";
	return value.dump();
}

template <typename T>
std::string toString(T value) { return std::to_string(value); }

template <>
std::string toString<std::string>(std::string value) { return value; }

template <typename T>
std::string getValue(std::function<T()> getValue, std::string const & defaultValue, bool useQuotations = false) {
	try {
		if (useQuotations)
			return "\"" + toString(getValue()) + "\"";
		return toString(getValue());
	} catch (JsonValueIsNullException const &) {
		return defaultValue;
	}
}

void writePrintParameters(IOption *, std::istream &, std::ostream & out, std::string const & endline, PaintDataContainer * container) {
	std::string const defaultValue = "undefined";

	std::map<std::string const, std::string const> const specialValues = {
		{container->getPresetNameColumnName(), getValue<std::string>([&](){ return container->getPresetName(); }, defaultValue, true)},
		{PAINT_TYPE_COLUMN_NAME, getValue<std::string>([&](){ return container->getPaintTypeName(); }, defaultValue, true)},
		{MATERIAL_TYPE_COLUMN_NAME, getValue<std::string>([&](){ return container->getMaterialTypeName(); }, defaultValue, true)},
		{PAINT_CONSUMPTION_COLUMN_NAME, getValue<double>([&](){ return container->getPaintConsumption(); }, defaultValue, false)}
	};

	out << "Parameters' values:" << endline;
	for (std::string const & column : container->getColumnsNames()) {
		std::string value;
		auto pair = specialValues.find(column);
		if (pair != specialValues.end())
			value = pair->second;
		else
			value = dump(container->getData(column));

		out << column << ":\t" << value << endline;
	}
}

std::size_t readIndexItem(std::istream & in, std::ostream & out, std::string const & endline, std::vector<std::string> const & items) {
	std::string line;
	std::size_t len = items.size();
	std::getline(in, line);

	if (line == "")
		throw DefaultOptionIsChosenException();

	try {
		std::size_t res = std::stoul(line) - 1;
		if (res < len)
			return res;
	} catch (std::invalid_argument const &) {}

	throw std::invalid_argument("No such option \"" + line + "\"");
}

void setType(std::istream & in, std::ostream & out, std::string const & endline, std::vector<std::string> const & types, std::string const & category, std::function<std::size_t()> getIndex, std::function<std::string()> getName, std::function<void(std::size_t)> setIndex) {
	std::size_t count = 0;
	out << "Available " << category << "s are:" << endline;
	for (std::string const & type : types)
		out << ++count << '\t' << type << endline;
	out << endline;

	std::string defaultValue = getValue<std::string>([&](){ return std::to_string(getIndex() + 1); }, "undefined", true);
	out << "Current " << category << " is " << defaultValue << endline << endline;

	std::string prompt = "Enter option number (default=" + defaultValue + "): ";
	in.ignore();
	bool loop = true;
	while (loop) {
		try {
			out << prompt;
			setIndex(readIndexItem(in, out, endline, types));
			loop = false;
		} catch (DefaultOptionIsChosenException const & err) {
			out << err.what() << endline;
			loop = false;
		} catch (std::invalid_argument const & err) {
			out << err.what() << endline;
		}
	}

	out << category << ' ' << getValue<std::string>([&](){ return getName(); }, "undefined", true) << " is set" << endline;
}

void setPaintType(IOption *, std::istream & in, std::ostream & out, std::string const & endline, PaintDataContainer * container) {
	setType(
		in, out, endline, container->getConnection()->getPaintTypes(),
		"paint type",
		[&](){ return container->getPaintTypeIndex(); },
		[&](){ return container->getPaintTypeName(); },
		[&](std::size_t index){ container->setPaintType(index); }
	);
}

void setMaterialType(IOption *, std::istream & in, std::ostream & out, std::string const & endline, PaintDataContainer * container) {
	setType(
		in, out, endline, container->getConnection()->getMaterialTypes(),
		"material type",
		[&](){ return container->getMaterialTypeIndex(); },
		[&](){ return container->getMaterialTypeName(); },
		[&](std::size_t index){ container->setMaterialType(index); }
	);
}

template <typename T>
T readValue(std::istream & in, std::ostream & out, std::string const & endline, std::function<T(std::string const &)> converter) {
	std::string line;
	std::getline(in, line);

	if (line == "")
		throw DefaultOptionIsChosenException();

	try {
		return converter(line);
	} catch (std::invalid_argument const &) {}

	throw std::invalid_argument("Invalid value \"" + line + "\"");
}

template <typename T>
void setValue(std::istream & in, std::ostream & out, std::string const & endline, std::string const & category, std::function<T()> getValue, std::function<void(T)> setValue, std::function<T(std::string const &)> converter, std::function<void(T)> checker) {
	std::string defaultValue;
	out << "Current " << category << " value is ";
	try {
		defaultValue = std::to_string(getValue());
		out << defaultValue << " g/m^2";
	} catch (JsonValueIsNullException const &) {
		defaultValue = "undefined";
		out << defaultValue;
	}
	out << endline << endline;

	std::string const prompt = "Enter value (default=" + defaultValue + "): ";
	in.ignore();
	bool loop = true;
	while (loop) {
		try {
			out << prompt;
			T res = readValue<T>(in, out, endline, converter);
			checker(res);
			setValue(res);
			loop = false;
		} catch (DefaultOptionIsChosenException const & err) {
			out << err.what() << endline;
			loop = false;
		} catch (std::invalid_argument const & err) {
			out << err.what() << endline;
		}
	}

	out << category << " value ";
	try {
		out << getValue() << " is set";
	} catch (JsonValueIsNullException const &) {
		out << "is undefined";
	}
	out << endline;
}

void setPaintConsumption(IOption *, std::istream & in, std::ostream & out, std::string const & endline, PaintDataContainer * container) {
	setValue<double>(in, out, endline, "paint consumption",
		[&](){ return container->getPaintConsumption(); },
		[&](double value){ container->setPaintConsumption(value); },
		[](std::string const & line){ return std::stod(line); },
		[](double value) {
			if (value <= 0)
				throw std::invalid_argument("Value must be greater than 0");
		}
	);
}

void setDivider(IOption *, std::istream & in, std::ostream & out, std::string const & endline, PaintDataContainer * container) {
	setValue<double>(in, out, endline, "divider",
		[&](){ return container->getDivider(); },
		[&](double value){ container->setDivider(value); },
		[](std::string const & line){ return std::stod(line); },
		[](double value) {
			if (value <= 0)
				throw std::invalid_argument("Value must be greater than 0");
		}
	);
}

void setPercent(IOption *, std::istream & in, std::ostream & out, std::string const & endline, PaintDataContainer * container) {
	setValue<double>(in, out, endline, "print percent",
		[&](){ return container->getPercent(); },
		[&](double value){ container->setPercent(value); },
		[](std::string const & line){ return std::stod(line); },
		[](double value) {
			if (value <= 0 || value > 100)
				throw std::invalid_argument("Value must be greater than 0 and must not exceed 100");
		}
	);
}

void setWidth(IOption *, std::istream & in, std::ostream & out, std::string const & endline, PaintDataContainer * container) {
	setValue<double>(in, out, endline, "sheet width",
		[&](){ return container->getWidth(); },
		[&](double value){ container->setWidth(value); },
		[](std::string const & line){ return std::stod(line); },
		[](double value) {
			if (value <= 0)
				throw std::invalid_argument("Value must be greater than 0");
		}
	);
}

void setLength(IOption *, std::istream & in, std::ostream & out, std::string const & endline, PaintDataContainer * container) {
	setValue<double>(in, out, endline, "sheet length",
		[&](){ return container->getLength(); },
		[&](double value){ container->setLength(value); },
		[](std::string const & line){ return std::stod(line); },
		[](double value) {
			if (value <= 0)
				throw std::invalid_argument("Value must be greater than 0");
		}
	);
}

void setCirculation(IOption *, std::istream & in, std::ostream & out, std::string const & endline, PaintDataContainer * container) {
	setValue<std::size_t>(in, out, endline, "circulation",
		[&](){ return container->getCirculation(); },
		[&](std::size_t value){ container->setCirculation(value); },
		[](std::string const & line){ return std::stoul(line); },
		[](std::size_t value) {
			if (value <= 0)
				throw std::invalid_argument("Value must be greater than 0");
		}
	);
}

void setPaintReserve(IOption *, std::istream & in, std::ostream & out, std::string const & endline, PaintDataContainer * container) {
	setValue<double>(in, out, endline, "paint reserve",
		[&](){ return container->getPaintReserve(); },
		[&](double value){ container->setPaintReserve(value); },
		[](std::string const & line){ return std::stod(line); },
		[](double value) {
			if (value <= 0)
				throw std::invalid_argument("Value must be greater than 0");
		}
	);
}

void loadPreset(IOption *, std::istream & in, std::ostream & out, std::string const & endline, PaintDataContainer * container) {
	IConnection * conn = container->getConnection();
	std::vector<std::string> presets = conn->getPresetsNames( PAINT_CALCULATION_TABLE_NAME);
	setType(
		in, out, endline, presets,
		"paint calculation preset",
		[&](){ return conn->getPresetIndex(PAINT_CALCULATION_TABLE_NAME, container->getPresetName()); },
		[&](){ return container->getPresetName(); },
		[&](std::size_t index){ container->setPresetName(presets[index]); }
	);
}

int main() {

	std::fstream file("../data/paint.json");
	IConnection * conn = new JsonConnection(file);

	PaintDataContainer paintCalculationContainer(conn);

	CustomLeafOption<PaintDataContainer *> writePrintParametersOption(
		"write values of parameters",
		"Print current values of all paint calculation mode parameters",
		writePrintParameters,
		&paintCalculationContainer
	);

	CustomLeafOption<PaintDataContainer *> setPaintTypeOption(
		"set paint type",
		"Set type of paint you are going to use",
		setPaintType,
		&paintCalculationContainer);

	CustomLeafOption<PaintDataContainer *> setMaterialTypeOption(
		"set material type",
		"Set type of material you are going to use",
		setMaterialType,
		&paintCalculationContainer);

	CustomLeafOption<PaintDataContainer *> setPaintConsumptionOption(
		"set paint consumption",
		"Set paint consumption value manually (paint and material type settings clears if a user enters a new value)",
		setPaintConsumption,
		&paintCalculationContainer
	);

	CustomLeafOption<PaintDataContainer *> setDividerOption(
		"set divider",
		"Set divider of formula",
		setDivider,
		&paintCalculationContainer
	);

	CustomLeafOption<PaintDataContainer *> setPercentOption(
		"set printing percent",
		"Set percentage of sheet sealing",
		setPercent,
		&paintCalculationContainer
	);

	CustomLeafOption<PaintDataContainer *> setWidthOption(
		"set sheet width",
		"Set width value of the sheet",
		setWidth,
		&paintCalculationContainer
	);

	CustomLeafOption<PaintDataContainer *> setLengthOption(
		"set sheet width",
		"Set width value of the sheet",
		setLength,
		&paintCalculationContainer
	);

	CustomLeafOption<PaintDataContainer *> setCirculationOption(
		"set circulation",
		"set amount of edition",
		setCirculation,
		&paintCalculationContainer
	);

	CustomLeafOption<PaintDataContainer *> setPaintReserveOption(
		"set paint reserve",
		"set minimal amount of paint for an edition",
		setPaintReserve,
		&paintCalculationContainer
	);

	CustomLeafOption<PaintDataContainer *> loadPresetOption(
		"load preset",
		"load values of existing preset",
		loadPreset,
		&paintCalculationContainer
	);

	BaseOptionContainer paintCalculation("paint calculation", "contains options to work with paint calculation data", {
		{'w', &writePrintParametersOption},
		{'p', &setPaintTypeOption},
		{'m', &setMaterialTypeOption},
		{'c', &setPaintConsumptionOption},
		{'d', &setDividerOption},
		{'%', &setPercentOption},
		{'W', &setWidthOption},
		{'L', &setLengthOption},
		{'C', &setCirculationOption},
		{'r', &setPaintReserveOption},
		{'l', &loadPresetOption}
	});

	BaseOptionContainer root("root", BASE_HELP_TEXT, {
		{'p', &paintCalculation}
	}, true);
	root.exec(0, std::cin, std::cout, "\n");

	delete conn;

	return 0;
}
