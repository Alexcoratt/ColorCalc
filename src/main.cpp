#include "detail/exceptions.hpp"
#include "json_fwd.hpp"
#include <asm-generic/errno.h>
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

template <typename T>
T readValue(std::istream & in, std::function<T(std::string const &)> converter) {
	std::string line;
	std::getline(in, line);

	if (line == "")
		throw DefaultOptionIsChosenException();

	return converter(line);
}

std::size_t readIndexItem(std::istream & in, std::size_t itemCount) {
	return readValue<std::size_t>(
		in,
		[&](std::string const & line) {
			try {
				std::size_t value = std::stoul(line) - 1;
				if (value < itemCount)
					return value;
			} catch (std::invalid_argument const &) {}
			throw std::invalid_argument("No such option \"" + line + "\"");
		}
	);
}

void setValue(std::function<void()> intro, std::function<void()> prompt, std::function<void()> setItem, std::function<void(char const *)> printErrWhat, std::function<void()> outro) {
	intro();
	bool loop = true;
	while (loop) {
		try {
			prompt();
			setItem();
			loop = false;
		} catch (DefaultOptionIsChosenException const & err) {
			printErrWhat(err.what());
			loop = false;
		} catch (std::invalid_argument const & err) {
			printErrWhat(err.what());
		}
	}
	outro();
}

void setPaintType(IOption *, std::istream & in, std::ostream & out, std::string const & endline, PaintDataContainer * container) {
	std::vector<std::string> types = container->getConnection()->getPaintTypes();

	std::string const defaultValue = getValue<std::string>([&](){ return std::to_string(container->getPaintTypeIndex() + 1); }, "undefined", true);

	setValue(
		[&]() {
			out << "Available paint types are" << endline;
			std::size_t count = 0;
			for (auto type : types)
				out << ++count << '\t' << type << endline;
			out << endline;

			out << "Current paint type value is " << defaultValue << endline << endline;
			in.ignore();
		},
		[&]() {
			out << "Enter option (default=" << defaultValue << "): ";
		},
		[&]() {
			container->setPaintType(readIndexItem(in, types.size()));
		},
		[&](char const * line) {
			out << line << endline;
		},
		[&]() {
			out << "Paint type " << getValue<std::string>([&](){ return container->getPaintTypeName(); }, "undefined", true) << " is set";
		}
	);
}

void setMaterialType(IOption *, std::istream & in, std::ostream & out, std::string const & endline, PaintDataContainer * container) {
	std::vector<std::string> types = container->getConnection()->getMaterialTypes();
	std::string const defaultValue = getValue<std::string>([&](){ return std::to_string(container->getMaterialTypeIndex() + 1); }, "undefined", true);

	setValue(
		[&]() {
			out << "Available material types are" << endline;
			std::size_t count = 0;
			for (auto type : types)
				out << ++count << '\t' << type << endline;
			out << endline;

			out << "Current material type value is " << defaultValue << endline << endline;
			in.ignore();
		},
		[&]() {
			out << "Enter option (default=" << defaultValue << "): ";
		},
		[&]() {
			container->setMaterialType(readIndexItem(in, types.size()));
		},
		[&](char const * line) {
			out << line << endline;
		},
		[&]() {
			out << "Material type " << getValue<std::string>([&](){ return container->getMaterialTypeName(); }, "undefined", true) << " is set";
		}
	);
}

template <typename T>
void setValue(std::istream & in, std::ostream & out, std::string const & endline, std::string const & category, std::function<T()> getValue, std::function<void(T)> setValue, std::function<T(std::string const &)> converter, std::function<void(T)> checker) {
	std::string defaultValue;
	out << "Current " << category << " value is ";
	try {
		defaultValue = std::to_string(getValue());
		out << defaultValue;
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
			T res = readValue<T>(in, converter);
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

	std::string const defaultValue = getValue<std::string>([&](){ return std::to_string(conn->getPresetIndex(PAINT_CALCULATION_TABLE_NAME, container->getPresetName()) + 1); }, "undefined", true);

	setValue(
		[&]() {
			out << "Available presets are" << endline;
			std::size_t count = 0;
			for (auto preset : presets)
				out << ++count << '\t' << preset << endline;
			out << endline;

			out << "Current value is " << defaultValue << endline << endline;
			in.ignore();
		},
		[&]() {
			out << "Enter option (default=" << defaultValue << "): ";
		},
		[&]() {
			container->setPreset(presets[readIndexItem(in, presets.size())]);
		},
		[&](char const * line) {
			out << line << endline;
		},
		[&]() {
			out << "Preset " << getValue<std::string>([&](){ return container->getPresetName(); }, "undefined", true) << " is set";
		}
	);
}

bool readSubmit(std::istream & in, std::ostream & out, std::string const & endline, std::string const & message) {
	std::vector<std::string> const answers = {"yes", "no"};
	std::string const defaultValue = "2";
	bool res = false;

	setValue(
		[&]() {
			out << message << endline << 1 << '\t' << "yes" << endline << 2 << '\t' << "no" << endline << endline;
			in.ignore();
		},
		[&]() {
			out << "Enter option (default=" << defaultValue << "): ";
		},
		[&]() {
			if (readIndexItem(in, 2) == 0)
				res = true;
		},
		[&](char const * line) {
			out << line << endline;
		},
		[&]() {
			if (res)
				out << "Submitted" << endline;
			else
				out << "Cancelled" << endline;
		}
	);

	return res;
}

void clearValues(IOption *, std::istream & in, std::ostream & out, std::string const & endline, PaintDataContainer * container) {
	if (readSubmit(in, out, endline, "Are you surely want to clear all values?"))
		container->clearData();
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

	CustomLeafOption<PaintDataContainer *> clearValuesOption(
		"remove values",
		"Clears data from every paint calculation value",
		clearValues,
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
		{'l', &loadPresetOption},
		{'R', &clearValuesOption}
	});

	BaseOptionContainer root("root", BASE_HELP_TEXT, {
		{'p', &paintCalculation}
	}, true);
	root.exec(0, std::cin, std::cout, "\n");

	delete conn;

	return 0;
}
