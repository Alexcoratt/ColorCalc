#include <cstddef>
#include <exception>
#include <stdexcept>
#include <iostream>
#include <string>
#include <vector>
#include <functional>

#include "DefaultOptionIsChosenExcepion.hpp"
#include "PaintDataContainer.hpp"
#include "AbstractDataContainer.hpp"
#include "UndefinedValueException.hpp"
#include "option_methods.hpp"
#include "common_methods.hpp"

namespace com = common_option_methods;
namespace pcom = paint_calculation_option_methods;
namespace lcom = lacquer_calculation_option_methods;

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
	std::cout << "Default value is set" << std::endl;
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

void setType(std::vector<std::string> const & types, std::function<std::string()> get, std::function<void(std::string)> set) {
	std::size_t defaultVariant;
	bool defaultVariantIsDefined = false;
	std::string prompt;
	try {
		defaultVariant = common_methods::getIndex(types, get());
		prompt = "Enter index of the variant (default=" + std::to_string(defaultVariant + 1) + "): ";
		defaultVariantIsDefined = true;
	} catch (UndefinedValueException const & err) {
		prompt = "Enter index of the variant (default=undefined): ";
	}

	try {
		std::size_t variant = readVariant(prompt, types);
		if (!defaultVariantIsDefined || variant != defaultVariant)
			set(types[variant]);
	} catch (DefaultOptionIsChosenException const & err) {}
}

void com::loadPreset(AbstractDataContainer * container) {
	std::vector<std::string> presets = container->getAvailablePresetsNames();

	std::cout << "Select the preset to load" << std::endl;
	setType(
		presets,
		[&]() { return container->getPresetName(); },
		[&](std::string name) { container->setPreset(name); }
	);

	std::cout << "Preset ";
	try {
		std::string presetName = container->getPresetName();
		std::cout << "named \"" << presetName << "\" is loaded" << std::endl;
	} catch (UndefinedValueException const &) {
		std::cout << "is undefined" << std::endl;
	}
}

void com::clearValues(AbstractDataContainer * container) {
	std::vector<std::string> const variants = {"no", "yes"};
	int answer = 0;

	std::cout << "Clear all paint calculation fields" << std::endl;
	std::cout << "Are you sure you want to clear fields?" << std::endl;
	setType(
		variants,
		[&]() { return variants[answer]; },
		[&](std::string variant) { answer = common_methods::getIndex(variants, variant); }
	);

	if (answer == 1) {
		container->clearData();
		std::cout << "Submitted" << std::endl << "Fields are cleared" << std::endl;
	} else
		std::cout << "Aborted" << std::endl;
}

void com::calculateResourceAmount(AbstractDataContainer const * container) {
	try {
		double paintAmount = container->calculate();
		std::cout << "Required amount equals " << paintAmount << "kg" << std::endl;
	} catch (UndefinedValueException const & err) {
		std::cerr << "Error: " << err.what() << std::endl;
	}
}

void com::writePaintParameters(AbstractDataContainer const * container) {
	std::cout << "Preset name:\t";
	try {
		std::cout << container->getPresetName() << std::endl;
	} catch (UndefinedValueException const &) {
		std::cout << "null" << std::endl;
	}

	std::vector<std::string> const columns = container->getParamNames();
	nlohmann::json data = container->exportData();
	for (std::string const & column : columns)
		std::cout << column << ":\t" << data[column].dump() << std::endl;
}

void pcom::setPaintType(PaintDataContainer * container) {
	std::cout << "Select paint type" << std::endl;
	setType(
		container->getConnection()->getPaintTypes(),
		[&]() { return container->getPaintType(); },
		[&](std::string type) { container->setPaintType(type); }
	);

	std::cout << "Paint type ";
	try {
		std::string type = container->getPaintType();
		std::cout << "\"" << type << "\" is set" << std::endl;
	} catch (UndefinedValueException const &) {
		std::cout << "is undefined" << std::endl;
	}
}

void pcom::setMaterialType(PaintDataContainer * container) {
	std::cout << "Select material type" << std::endl;
	setType(
		container->getConnection()->getMaterialTypes(),
		[&]() { return container->getMaterialType(); },
		[&](std::string type) { container->setMaterialType(type); }
	);

	std::cout << "Material type ";
	try {
		std::string type = container->getMaterialType();
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

void pcom::setConsumption(PaintDataContainer * container) {
	std::cout << "Set paint consumption value" << std::endl;

	setValue<double> (
		[&container]() { return container->getPaintConsumption(); },
		[&container](double value) { container->setPaintConsumption(value); },
		[](std::string line) { return std::stod(line); },
		[](double value) {
			if (value > 0)
				return true;
			throw std::invalid_argument("value must be greater than 0");
		}
	);

	std::cout << "Paint consumption ";
	try {
		auto paintConsumption = container->getPaintConsumption();
		std::cout << "value " << paintConsumption << " is set" << std::endl;
	} catch (UndefinedValueException const &) {
		std::cout << "is undefined" << std::endl;
	}
}

void pcom::setDivider(PaintDataContainer * container) {
	std::cout << "Set divider value" << std::endl;

	setValue<double> (
		[&container]() { return container->getDivider(); },
		[&container](double value) { container->setDivider(value); },
		[](std::string line) { return std::stod(line); },
		[](double value) {
			if (value > 0)
				return true;
			throw std::invalid_argument("value must be greater than 0");
		}
	);

	std::cout << "Divider ";
	try {
		auto divider = container->getDivider();
		std::cout << "value " << divider << " is set" << std::endl;
	} catch (UndefinedValueException const &) {
		std::cout << "is undefined" << std::endl;
	}
}

void pcom::setPercentage(PaintDataContainer * container) {
	std::cout << "Set percentage value" << std::endl;

	setValue<double> (
		[&container]() { return container->getPercentage(); },
		[&container](double value) { container->setPercentage(value); },
		[](std::string line) { return std::stod(line); },
		[](double value) {
			if (value > 0 && value <= 100)
				return true;
			throw std::invalid_argument("value must be greater than 0 and not greater than 100");
		}
	);

	std::cout << "Percentage ";
	try {
		auto percentage = container->getPercentage();
		std::cout << "value " << percentage << " is set" << std::endl;
	} catch (UndefinedValueException const &) {
		std::cout << "is undefined" << std::endl;
	}
}

void pcom::setSheetWidth(PaintDataContainer * container) {
	std::cout << "Set sheet width value" << std::endl;

	setValue<double> (
		[&container]() { return container->getSheetWidth(); },
		[&container](double value) { container->setSheetWidth(value); },
		[](std::string line) { return std::stod(line); },
		[](double value) {
			if (value > 0)
				return true;
			throw std::invalid_argument("value must be greater than 0");
		}
	);

	std::cout << "Sheet width ";
	try {
		auto sheetWidth = container->getSheetWidth();
		std::cout << "value " << sheetWidth << " is set" << std::endl;
	} catch (UndefinedValueException const &) {
		std::cout << "is undefined" << std::endl;
	}
}

void pcom::setSheetLength(PaintDataContainer * container) {
	std::cout << "Set sheet length value" << std::endl;

	setValue<double> (
		[&container]() { return container->getSheetLength(); },
		[&container](double value) { container->setSheetLength(value); },
		[](std::string line) { return std::stod(line); },
		[](double value) {
			if (value > 0)
				return true;
			throw std::invalid_argument("value must be greater than 0");
		}
	);

	std::cout << "Sheet length ";
	try {
		auto sheetLength = container->getSheetLength();
		std::cout << "value " << sheetLength << " is set" << std::endl;
	} catch (UndefinedValueException const &) {
		std::cout << "is undefined" << std::endl;
	}
}

void pcom::setCirculation(PaintDataContainer * container) {
	std::cout << "Set circulation value" << std::endl;

	setValue<unsigned long> (
		[&container]() { return container->getCirculation(); },
		[&container](unsigned long value) { container->setCirculation(value); },
		[](std::string line) { return std::stoul(line); },
		[](unsigned long value) {
			if (value > 0)
				return true;
			throw std::invalid_argument("value must be greater than 0");
		}
	);

	std::cout << "Circulation ";
	try {
		auto circulation = container->getCirculation();
		std::cout << "value " << circulation << " is set" << std::endl;
	} catch (UndefinedValueException const &) {
		std::cout << "is undefined" << std::endl;
	}
}

void pcom::setReserve(PaintDataContainer * container) {
	std::cout << "Set paint reserve value" << std::endl;

	setValue<double>(
		[&container]() { return container->getPaintReserve(); },
		[&container](double value) { container->setPaintReserve(value); },
		[](std::string line) { return std::stod(line); },
		[](double value) {
			if (value > 0)
				return true;
			throw std::invalid_argument("value must be greater than 0");
		}
	);

	std::cout << "Paint reserve ";
	try {
		auto paintReserve = container->getPaintReserve();
		std::cout << "value " << paintReserve << " is set" << std::endl;
	} catch (UndefinedValueException const &) {
		std::cout << "is undefined" << std::endl;
	}
}

void lcom::setPercentage(LacquerDataContainer * container) {
	std::cout << "Set percentage of lacquer coverage" << std::endl;

	setValue<double>(
		[&container]() { return container->getPercentage(); },
		[&container](double value) { container->setPercentage(value); },
		[](std::string line) { return std::stod(line); },
		[](double value) {
			if (value > 0 && value <= 100)
				return true;
			throw std::invalid_argument("value must be greater than 0 and not greater than 100");
		}
	);

	std::cout << "Lacquer coverage percentage ";
	try {
		auto value = container->getPercentage();
		std::cout << "value " << value << " is set" << std::endl;
	} catch (UndefinedValueException const &) {
		std::cout << "is undefined" << std::endl;
	}
}

void lcom::setConsumption(LacquerDataContainer * container) {
	std::cout << "Set consumption of lacquer" << std::endl;

	setValue<double>(
		[&container]() { return container->getLacquerConsumption(); },
		[&container](double value) { container->setLacquerConsumption(value); },
		[](std::string line) { return std::stod(line); },
		[](double value) {
			if (value > 0)
				return true;
			throw std::invalid_argument("value must be greater than 0");
		}
	);

	std::cout << "Lacquer consumption ";
	try {
		auto value = container->getLacquerConsumption();
		std::cout << "value " << value << " is set" << std::endl;
	} catch (UndefinedValueException const &) {
		std::cout << "is undefined" << std::endl;
	}
}

void lcom::setSheetLength(LacquerDataContainer * container) {
	std::cout << "Set length of the sheet" << std::endl;

	setValue<double>(
		[&container]() { return container->getSheetLength(); },
		[&container](double value) { container->setSheetLength(value); },
		[](std::string line) { return std::stod(line); },
		[](double value) {
			if (value > 0)
				return true;
			throw std::invalid_argument("value must be greater than 0");
		}
	);

	std::cout << "Length of the sheet ";
	try {
		auto value = container->getSheetLength();
		std::cout << "value " << value << " is set" << std::endl;
	} catch (UndefinedValueException const &) {
		std::cout << "is undefined" << std::endl;
	}
}

void lcom::setSheetWidth(LacquerDataContainer * container) {
	std::cout << "Set width of the sheet" << std::endl;

	setValue<double>(
		[&container]() { return container->getSheetWidth(); },
		[&container](double value) { container->setSheetWidth(value); },
		[](std::string line) { return std::stod(line); },
		[](double value) {
			if (value > 0)
				return true;
			throw std::invalid_argument("value must be greater than 0");
		}
	);

	std::cout << "Width of the sheet ";
	try {
		auto value = container->getSheetWidth();
		std::cout << "value " << value << " is set" << std::endl;
	} catch (UndefinedValueException const &) {
		std::cout << "is undefined" << std::endl;
	}
}

void lcom::setCircualtion(LacquerDataContainer * container) {
	std::cout << "Set circulation" << std::endl;

	setValue<std::size_t>(
		[&container]() { return container->getCirculation(); },
		[&container](std::size_t value) { container->setCirculation(value); },
		[](std::string line) { return std::stoul(line); },
		[](std::size_t value) {
			if (value > 0)
				return true;
			throw std::invalid_argument("value must be greater than 0");
		}
	);

	std::cout << "Circulation ";
	try {
		auto value = container->getCirculation();
		std::cout << "value " << value << " is set" << std::endl;
	} catch (UndefinedValueException const &) {
		std::cout << "is undefined" << std::endl;
	}
}
