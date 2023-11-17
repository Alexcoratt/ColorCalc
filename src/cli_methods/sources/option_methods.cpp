#include <cstddef>
#include <exception>
#include <stdexcept>
#include <iostream>
#include <string>
#include <vector>
#include <functional>

#include "DefaultOptionIsChosenExcepion.hpp"
#include <PaintDataDispatcher.hpp>
#include <AbstractDataDispatcher.hpp>
#include "UndefinedValueException.hpp"
#include "option_methods.hpp"

namespace com = common_option_methods;
namespace pcom = paint_calculation_option_methods;
namespace lcom = lacquer_calculation_option_methods;
namespace fcom = foil_calculation_option_methods;

template <typename T>
inline std::size_t getIndex(std::vector<T> const & vect, T search) {
	std::size_t count = 0;
	for (T value : vect) {
		if (value == search)
			return count;
		++count;
	}
	throw std::invalid_argument("getIndex: required value is not found");
}

template <typename T>
T readValue(std::string const & prompt, std::function<T(std::string)> converter, std::function<bool(T)> checker = [](T) { return true; }) {
	std::string line;
	std::cin.ignore();
	while (std::cout << prompt && std::getline(std::cin, line)) {
		if (line.size() < 1)
			break;
		try {
			T res = converter(line);
			if (checker(res))
				return res;
		} catch (std::exception const & err) {
			std::cerr << "Invalid value \'" << line << "\'" << std::endl;
			std::cerr << "Error: " << err.what() << std::endl;
		}
	}
	throw DefaultOptionIsChosenException();
}

std::size_t readVariant(std::string const & prompt, std::vector<std::string> variants) {
	std::cout << "Avilable variants" << std::endl;
	std::size_t count = 0;
	for (std::string const & variant : variants)
		std::cout << ++count << '\t' << variant << std::endl;

	return readValue<std::size_t>(
		prompt,
		[](std::string line) { return std::stoul(line) - 1; },
		[&variants](std::size_t value) {
			if (value < variants.size())
				return true;
			throw std::invalid_argument("there is no such option");
		}
	);
}

void setVariant(std::vector<std::string> const & types, std::function<std::string()> get, std::function<void(std::string)> set) {
	std::string prompt;
	AutoValue defaultVariant;
	try {
		defaultVariant = getIndex(types, get());
	} catch (std::invalid_argument const &) {
		defaultVariant.clear();
	} catch (UndefinedValueException const &) {
		defaultVariant.clear();
	}

	if (defaultVariant.isNull())
		prompt = "Enter index of the variant (default=undefined): ";
	else
		prompt = "Enter index of the variant (default=" + std::to_string((std::size_t)defaultVariant + 1) + "): ";

	set(types[readVariant(prompt, types)]);
}

void com::clearValues(AbstractDataDispatcher * dispatcher) {
	std::vector<std::string> const variants = {"no", "yes"};
	int answer = 0;

	std::cout << "Clear all parameters" << std::endl;
	std::cout << "Are you sure you want to clear parameters?" << std::endl;
	try {
		setVariant(
			variants,
			[&]() { return variants[answer]; },
			[&](std::string variant) { answer = getIndex(variants, variant); }
		);
	} catch (DefaultOptionIsChosenException const &) {}

	if (answer == 1) {
		dispatcher->clear();
		std::cout << "Submitted" << std::endl << "Fields are cleared" << std::endl;
	} else
		std::cout << "Aborted" << std::endl;
}

void com::calculateResourceAmount(AbstractDataDispatcher const * dispatcher) {
	double res = dispatcher->calculate();
	std::cout << "Required amount equals " << res << "kg" << std::endl;
}

void com::writeParameters(AbstractDataDispatcher const * dispatcher) {
	try {
		auto presetName = dispatcher->getPresetName();
		std::cout << "Preset name:\t" << presetName << std::endl << std::endl;
	} catch (UndefinedValueException const &) {}

	auto params = dispatcher->toStringMap();
	for (auto iter = params.begin(); iter != params.end(); ++iter)
		std::cout << iter->first << ":\t" << iter->second << std::endl;
}

void com::createPreset(AbstractDataDispatcher * dispatcher) {
	std::cout << "Enter name of the new preset (leave field empty to abort operation)" << std::endl;

	try {
		std::string name = readValue<std::string>(
			"Enter name (default=abort): ",
			[](std::string line) { return line; }
		);
		dispatcher->createPreset(name);
		std::cout << "Preset named \"" << name << "\" created" << std::endl;
	} catch (DefaultOptionIsChosenException const &) {
		std::cout << "Aborted" << std::endl;
	}
}

void com::updatePreset(AbstractDataDispatcher * dispatcher) {
	std::vector<std::string> presets = dispatcher->getAvailablePresetNames();

	std::cout << "Select name of the preset you want to update (leave field empty to abort operation)" << std::endl;
	std::string presetName;

	try {
		setVariant(
			presets,
			[]() { return "abort"; },
			[&](std::string name) {
				dispatcher->updatePreset(name);
				presetName = name;
			}
		);
		std::cout << "Preset named \"" << presetName << "\" updated" << std::endl;
	} catch (DefaultOptionIsChosenException const &) {
		std::cout << "Aborted" << std::endl;
	}
}

void com::removePreset(AbstractDataDispatcher * dispatcher) {
	std::vector<std::string> presets = dispatcher->getAvailablePresetNames();

	std::cout << "Select name of the paint calculation preset you want to remove (leave field empty to abort operation)" << std::endl;
	std::string presetName;

	try {
		setVariant(
			presets,
			[]() { return "abort"; },
			[&](std::string name) {
				dispatcher->removePreset(name);
				presetName = name;
			}
		);
		std::cout << "Preset named \"" << presetName << "\" removed" << std::endl;
	} catch (DefaultOptionIsChosenException const &) {
		std::cout << "Aborted" << std::endl;
	}
}


void pcom::setPaintType(PaintDataDispatcher * dispatcher) {
	std::cout << "Select paint type" << std::endl;
	try {
		setVariant(
			dispatcher->getConnection()->getPaintTypes(),
			[&]() { return dispatcher->getPaintType(); },
			[&](std::string type) { dispatcher->setPaintType(type); }
		);
	} catch (DefaultOptionIsChosenException const &) {}

	std::cout << "Paint type ";
	try {
		std::string type = dispatcher->getPaintType();
		std::cout << "\"" << type << "\" is set" << std::endl;
	} catch (UndefinedValueException const &) {
		std::cout << "is undefined" << std::endl;
	}
}

void pcom::setMaterialType(PaintDataDispatcher * dispatcher) {
	std::cout << "Select material type" << std::endl;
	try {
		setVariant(
			dispatcher->getConnection()->getMaterialTypes(),
			[&]() { return dispatcher->getMaterialType(); },
			[&](std::string type) { dispatcher->setMaterialType(type); }
		);
	} catch (DefaultOptionIsChosenException const &) {}

	std::cout << "Material type ";
	try {
		std::string type = dispatcher->getMaterialType();
		std::cout << "\"" << type << "\" is set" << std::endl;
	} catch (UndefinedValueException const &) {
		std::cout << "is undefined" << std::endl;
	}
}

template <typename T>
void setValue(std::function<T()> getter, std::function<void(T)> setter, std::function<T(std::string)> converter, std::function<bool(T)> checker) {
	T defaultValue;
	bool defaultValueIsDefined = false;

	std::string prompt;
	try {
		defaultValue = getter();
		prompt = "Enter value (default=" + std::to_string(defaultValue) + "): ";
		defaultValueIsDefined = true;
	} catch (UndefinedValueException const &) {
		prompt = "Enter value (default=undefined): ";
	}

	try {
		T value = readValue<T>(prompt, converter, checker);
		if (!defaultValueIsDefined || value != defaultValue)
			setter(value);
	} catch (DefaultOptionIsChosenException const &) {}
}

void pcom::setConsumption(PaintDataDispatcher * dispatcher) {
	std::cout << "Set paint consumption value" << std::endl;

	setValue<double> (
		[&]() { return dispatcher->getPaintConsumption(); },
		[&](double value) { dispatcher->setPaintConsumption(value); },
		[](std::string line) { return std::stod(line); },
		[](double value) {
			if (value > 0)
				return true;
			throw std::invalid_argument("value must be greater than 0");
		}
	);

	std::cout << "Paint consumption ";
	try {
		auto paintConsumption = dispatcher->getPaintConsumption();
		std::cout << "value " << paintConsumption << " is set" << std::endl;
	} catch (UndefinedValueException const &) {
		std::cout << "is undefined" << std::endl;
	}
}

void pcom::setDivider(PaintDataDispatcher * dispatcher) {
	std::cout << "Set divider value" << std::endl;

	setValue<double> (
		[&]() { return dispatcher->getDivider(); },
		[&](double value) { dispatcher->setDivider(value); },
		[](std::string line) { return std::stod(line); },
		[](double value) {
			if (value > 0)
				return true;
			throw std::invalid_argument("value must be greater than 0");
		}
	);

	std::cout << "Divider ";
	try {
		auto divider = dispatcher->getDivider();
		std::cout << "value " << divider << " is set" << std::endl;
	} catch (UndefinedValueException const &) {
		std::cout << "is undefined" << std::endl;
	}
}

void pcom::setPercentage(PaintDataDispatcher * dispatcher) {
	std::cout << "Set percentage value" << std::endl;

	setValue<double> (
		[&]() { return dispatcher->getPercentage(); },
		[&](double value) { dispatcher->setPercentage(value); },
		[](std::string line) { return std::stod(line); },
		[](double value) {
			if (value > 0 && value <= 100)
				return true;
			throw std::invalid_argument("value must be greater than 0 and not greater than 100");
		}
	);

	std::cout << "Percentage ";
	try {
		auto percentage = dispatcher->getPercentage();
		std::cout << "value " << percentage << " is set" << std::endl;
	} catch (UndefinedValueException const &) {
		std::cout << "is undefined" << std::endl;
	}
}

void pcom::setSheetWidth(PaintDataDispatcher * dispatcher) {
	std::cout << "Set sheet width value" << std::endl;

	setValue<double> (
		[&]() { return dispatcher->getSheetWidth(); },
		[&](double value) { dispatcher->setSheetWidth(value); },
		[](std::string line) { return std::stod(line); },
		[](double value) {
			if (value > 0)
				return true;
			throw std::invalid_argument("value must be greater than 0");
		}
	);

	std::cout << "Sheet width ";
	try {
		auto sheetWidth = dispatcher->getSheetWidth();
		std::cout << "value " << sheetWidth << " is set" << std::endl;
	} catch (UndefinedValueException const &) {
		std::cout << "is undefined" << std::endl;
	}
}

void pcom::setSheetLength(PaintDataDispatcher * dispatcher) {
	std::cout << "Set sheet length value" << std::endl;

	setValue<double> (
		[&]() { return dispatcher->getSheetLength(); },
		[&](double value) { dispatcher->setSheetLength(value); },
		[](std::string line) { return std::stod(line); },
		[](double value) {
			if (value > 0)
				return true;
			throw std::invalid_argument("value must be greater than 0");
		}
	);

	std::cout << "Sheet length ";
	try {
		auto sheetLength = dispatcher->getSheetLength();
		std::cout << "value " << sheetLength << " is set" << std::endl;
	} catch (UndefinedValueException const &) {
		std::cout << "is undefined" << std::endl;
	}
}

void pcom::setCirculation(PaintDataDispatcher * dispatcher) {
	std::cout << "Set circulation value" << std::endl;

	setValue<unsigned long> (
		[&]() { return dispatcher->getCirculation(); },
		[&](unsigned long value) { dispatcher->setCirculation(value); },
		[](std::string line) { return std::stoul(line); },
		[](unsigned long value) {
			if (value > 0)
				return true;
			throw std::invalid_argument("value must be greater than 0");
		}
	);

	std::cout << "Circulation ";
	try {
		auto circulation = dispatcher->getCirculation();
		std::cout << "value " << circulation << " is set" << std::endl;
	} catch (UndefinedValueException const &) {
		std::cout << "is undefined" << std::endl;
	}
}

void pcom::setReserve(PaintDataDispatcher * dispatcher) {
	std::cout << "Set paint reserve value" << std::endl;

	setValue<double>(
		[&]() { return dispatcher->getPaintReserve(); },
		[&](double value) { dispatcher->setPaintReserve(value); },
		[](std::string line) { return std::stod(line); },
		[](double value) {
			if (value > 0)
				return true;
			throw std::invalid_argument("value must be greater than 0");
		}
	);

	std::cout << "Paint reserve ";
	try {
		auto paintReserve = dispatcher->getPaintReserve();
		std::cout << "value " << paintReserve << " is set" << std::endl;
	} catch (UndefinedValueException const &) {
		std::cout << "is undefined" << std::endl;
	}
}

void pcom::loadPaintPreset(PaintDataDispatcher * dispatcher) {
	std::vector<std::string> presets = dispatcher->getConnection()->getPaintPresetNames();

	std::cout << "Select the preset to load" << std::endl;
	try {
		setVariant(
			presets,
			[&]() { return dispatcher->getPresetName(); },
			[&](std::string name) { dispatcher->setPreset(name); }
		);
		std::cout << "Preset ";
		std::string presetName = dispatcher->getPresetName();
		std::cout << "named \"" << presetName << "\" is loaded" << std::endl;
		return;
	} catch (DefaultOptionIsChosenException const &) {
	} catch (UndefinedValueException const &) {}
	std::cout << "is undefined" << std::endl;
}


void lcom::setPercentage(LacquerDataDispatcher * dispatcher) {
	std::cout << "Set percentage of lacquer coverage" << std::endl;

	setValue<double>(
		[&]() { return dispatcher->getPercentage(); },
		[&](double value) { dispatcher->setPercentage(value); },
		[](std::string line) { return std::stod(line); },
		[](double value) {
			if (value > 0 && value <= 100)
				return true;
			throw std::invalid_argument("value must be greater than 0 and not greater than 100");
		}
	);

	std::cout << "Lacquer coverage percentage ";
	try {
		auto value = dispatcher->getPercentage();
		std::cout << "value " << value << " is set" << std::endl;
	} catch (UndefinedValueException const &) {
		std::cout << "is undefined" << std::endl;
	}
}

void lcom::setConsumption(LacquerDataDispatcher * dispatcher) {
	std::cout << "Set consumption of lacquer" << std::endl;

	setValue<double>(
		[&]() { return dispatcher->getLacquerConsumption(); },
		[&](double value) { dispatcher->setLacquerConsumption(value); },
		[](std::string line) { return std::stod(line); },
		[](double value) {
			if (value > 0)
				return true;
			throw std::invalid_argument("value must be greater than 0");
		}
	);

	std::cout << "Lacquer consumption ";
	try {
		auto value = dispatcher->getLacquerConsumption();
		std::cout << "value " << value << " is set" << std::endl;
	} catch (UndefinedValueException const &) {
		std::cout << "is undefined" << std::endl;
	}
}

void lcom::setSheetLength(LacquerDataDispatcher * dispatcher) {
	std::cout << "Set length of the sheet" << std::endl;

	setValue<double>(
		[&]() { return dispatcher->getSheetLength(); },
		[&](double value) { dispatcher->setSheetLength(value); },
		[](std::string line) { return std::stod(line); },
		[](double value) {
			if (value > 0)
				return true;
			throw std::invalid_argument("value must be greater than 0");
		}
	);

	std::cout << "Length of the sheet ";
	try {
		auto value = dispatcher->getSheetLength();
		std::cout << "value " << value << " is set" << std::endl;
	} catch (UndefinedValueException const &) {
		std::cout << "is undefined" << std::endl;
	}
}

void lcom::setSheetWidth(LacquerDataDispatcher * dispatcher) {
	std::cout << "Set width of the sheet" << std::endl;

	setValue<double>(
		[&]() { return dispatcher->getSheetWidth(); },
		[&](double value) { dispatcher->setSheetWidth(value); },
		[](std::string line) { return std::stod(line); },
		[](double value) {
			if (value > 0)
				return true;
			throw std::invalid_argument("value must be greater than 0");
		}
	);

	std::cout << "Width of the sheet ";
	try {
		auto value = dispatcher->getSheetWidth();
		std::cout << "value " << value << " is set" << std::endl;
	} catch (UndefinedValueException const &) {
		std::cout << "is undefined" << std::endl;
	}
}

void lcom::setCircualtion(LacquerDataDispatcher * dispatcher) {
	std::cout << "Set circulation" << std::endl;

	setValue<std::size_t>(
		[&]() { return dispatcher->getCirculation(); },
		[&](std::size_t value) { dispatcher->setCirculation(value); },
		[](std::string line) { return std::stoul(line); },
		[](std::size_t value) {
			if (value > 0)
				return true;
			throw std::invalid_argument("value must be greater than 0");
		}
	);

	std::cout << "Circulation ";
	try {
		auto value = dispatcher->getCirculation();
		std::cout << "value " << value << " is set" << std::endl;
	} catch (UndefinedValueException const &) {
		std::cout << "is undefined" << std::endl;
	}
}

void lcom::loadLacquerPreset(LacquerDataDispatcher * dispatcher) {
	std::vector<std::string> presets = dispatcher->getConnection()->getLacquerPresetNames();

	std::cout << "Select the preset to load" << std::endl;
	try {
		setVariant(
			presets,
			[&]() { return dispatcher->getPresetName(); },
			[&](std::string name) { dispatcher->setPreset(name); }
		);
		std::cout << "Preset ";
		std::string presetName = dispatcher->getPresetName();
		std::cout << "named \"" << presetName << "\" is loaded" << std::endl;
		return;
	} catch (DefaultOptionIsChosenException const &) {
	} catch (UndefinedValueException const &) {}
	std::cout << "is undefined" << std::endl;
}


void fcom::setCirulation(FoilDataDispatcher * dispatcher) {
	std::cout << "Set circulation" << std::endl;

	setValue<std::size_t>(
		[&]() { return dispatcher->getCirculation(); },
		[&](std::size_t value) { dispatcher->setCirculation(value); },
		[](std::string line) { return std::stoul(line); },
		[](std::size_t value) {
			if (value > 0)
				return true;
			throw std::invalid_argument("value must be greater than 0");
		}
	);

	std::cout << "Circulation ";
	try {
		auto value = dispatcher->getCirculation();
		std::cout << "value " << value << " is set" << std::endl;
	} catch (UndefinedValueException const &) {
		std::cout << "is undefined" << std::endl;
	}
}

void fcom::setLength(FoilDataDispatcher * dispatcher) {
	std::cout << "Set length of the roller" << std::endl;

	setValue<double>(
		[&]() { return dispatcher->getLength(); },
		[&](double value) { dispatcher->setLength(value); },
		[](std::string line) { return std::stod(line); },
		[](double value) {
			if (value > 0)
				return true;
			throw std::invalid_argument("value must be greater than 0");
		}
	);

	std::cout << "Length of the roller ";
	try {
		auto value = dispatcher->getLength();
		std::cout << "value " << value << " is set" << std::endl;
	} catch (UndefinedValueException const &) {
		std::cout << "is undefined" << std::endl;
	}
}

void fcom::setSheetNumber(FoilDataDispatcher * dispatcher) {
	std::cout << "Set number of sheets" << std::endl;

	setValue<std::size_t>(
		[&]() { return dispatcher->getSheetNumber(); },
		[&](std::size_t value) { dispatcher->setSheetNumber(value); },
		[](std::string line) { return std::stoul(line); },
		[](std::size_t value) {
			if (value > 0)
				return true;
			throw std::invalid_argument("value must be greater than 0");
		}
	);

	std::cout << "Number of sheets ";
	try {
		auto value = dispatcher->getSheetNumber();
		std::cout << "value " << value << " is set" << std::endl;
	} catch (UndefinedValueException const &) {
		std::cout << "is undefined" << std::endl;
	}
}

void fcom::setWidthReserve(FoilDataDispatcher * dispatcher) {
	std::cout << "Set width reserve of the roller" << std::endl;

	setValue<double>(
		[&]() { return dispatcher->getWidthReserve(); },
		[&](double value) { dispatcher->setWidthReserve(value); },
		[](std::string line) { return std::stod(line); },
		[](double value) {
			if (value > 0)
				return true;
			throw std::invalid_argument("value must be greater than 0");
		}
	);

	std::cout << "Width reserve of the roller ";
	try {
		auto value = dispatcher->getLength();
		std::cout << "value " << value << " is set" << std::endl;
	} catch (UndefinedValueException const &) {
		std::cout << "is undefined" << std::endl;
	}
}

void fcom::loadFoilPreset(FoilDataDispatcher * dispatcher) {
	std::vector<std::string> presets = dispatcher->getConnection()->getFoilPresetNames();

	std::cout << "Select the preset to load" << std::endl;
	try {
		setVariant(
			presets,
			[&]() { return dispatcher->getPresetName(); },
			[&](std::string name) { dispatcher->setPreset(name); }
		);
		std::cout << "Preset ";
		std::string presetName = dispatcher->getPresetName();
		std::cout << "named \"" << presetName << "\" is loaded" << std::endl;
		return;
	} catch (DefaultOptionIsChosenException const &) {
	} catch (UndefinedValueException const &) {}
	std::cout << "is undefined" << std::endl;
}

void fcom::calculateFoilRollerLength(FoilDataDispatcher const * dispatcher) {
	double length = dispatcher->calculate();
	std::cout << "Required roller's length equals " << length << "m" << std::endl;
}
