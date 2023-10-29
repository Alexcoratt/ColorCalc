#include <cstddef>
#include <exception>
#include <stdexcept>
#include <iostream>
#include <string>
#include <vector>
#include <functional>

#include "DefaultOptionIsChosenExcepion.hpp"
#include "PaintDataContainer.hpp"
#include "UndefinedValueException.hpp"
#include "option_methods.hpp"
#include "common_methods.hpp"

namespace pcom = paint_calculation_option_methods;
//using json_type_error = nlohmann::json_abi_v3_11_2::detail::type_error;

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
			std::cerr << "Error:" << err.what() << std::endl;
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

void pcom::writePaintParameters(PaintDataContainer const * container) {
	std::vector<std::string> const columns = container->getColumns();
	nlohmann::json data = container->exportData();
	for (std::string const & column : columns)
		std::cout << column << ":\t" << data[column].dump() << std::endl;
}

void setType(std::vector<std::string> const & types, std::function<std::string()> get, std::function<void(std::string)> set, std::string const & category) {
	std::size_t defaultVariant;
	bool defaultVariantIsDefined = false;
	std::string prompt;
	try {
		defaultVariant = common_methods::getIndex(types, get());
		prompt = "Enter index of the variant (default=" + std::to_string(defaultVariant) + "): ";
		defaultVariantIsDefined = true;
	} catch (UndefinedValueException const & err) {
		prompt = "Enter index of the variant (default=undefined): ";
	}

	std::cout << "Select " << category << std::endl;
	try {
		std::size_t variant = readVariant(prompt, types);
		if (!defaultVariantIsDefined || variant != defaultVariant)
			set(types[variant]);
	} catch (DefaultOptionIsChosenException const & err) {}

	try {
		std::string type = get();
		std::cout << category << " \"" << type << "\" is set";
	} catch (UndefinedValueException const &) {
		std::cout << category << " is undefined";
	}
}

void pcom::setPaintType(PaintDataContainer * container) {
	setType(
		container->getConnection()->getPaintTypes(),
		[&]() { return container->getPaintType(); },
		[&](std::string type) { container->setPaintType(type); },
		"paint type"
	);
}

void pcom::setMaterialType(PaintDataContainer * container) {
	setType(
		container->getConnection()->getMaterialTypes(),
		[&]() { return container->getMaterialType(); },
		[&](std::string type) { container->setMaterialType(type); },
		"material type"
	);
}

/*
void pcom::setPaintConsumption(PaintDataContainer * container) {
	double defaultValue;
	bool defaultValueIsDefined = false;

	std::string prompt;
	try {
		defaultValue = container->getPaintConsumption();
		prompt = "Enter value (default=" + std::to_string(defaultValue) + "): ";
		defaultValueIsDefined = true;
	} catch (UndefinedValueException const &) {
		prompt = "Enter value (default=undefined): ";
	}

	try {
		double value = readValue<double>(
			prompt,
			[](std::string line) { return std::stod(line); },
			[](double value) {
				if (value > 0)
					return true;
				throw std::invalid_argument("value must be greater than 0");
			}
		);
		if (!defaultValueIsDefined || value != defaultValue)
			container->setPaintConsumption(value);
	} catch (DefaultOptionIsChosenException const &) {}

	try {
		std::cout << "Paint consumption value " << container->getPaintConsumption() << " is set";
	} catch (UndefinedValueException const &) {
		std::cout << "Paint consumption is undefined";
	}
}
*/

template <typename T>
void setValue(std::function<T()> getter, std::function<void(T)> setter, std::function<T(std::string)> converter, std::function<bool(T)> checker, std::string const & category) {
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

	try {
		std::cout << category << " value " << getter() << " is set" << std::endl;
	} catch (UndefinedValueException const &) {
		std::cout << category << " is undefined" << std::endl;
	}
}

void pcom::setPaintConsumption(PaintDataContainer * container) {
	setValue<double> (
		[&container]() { return container->getPaintConsumption(); },
		[&container](double value) { container->setPaintConsumption(value); },
		[](std::string line) { return std::stod(line); },
		[](double value) {
			if (value > 0)
				return true;
			throw std::invalid_argument("value must be greater than 0");
		},
		"paint consumption"
	);
}

void pcom::setDivider(PaintDataContainer * container) {
	setValue<double> (
		[&container]() { return container->getDivider(); },
		[&container](double value) { container->setDivider(value); },
		[](std::string line) { return std::stod(line); },
		[](double value) {
			if (value > 0)
				return true;
			throw std::invalid_argument("value must be greater than 0");
		},
		"divider"
	);
}

void pcom::setPercentage(PaintDataContainer * container) {
	setValue<double> (
		[&container]() { return container->getPercentage(); },
		[&container](double value) { container->setPercentage(value); },
		[](std::string line) { return std::stod(line); },
		[](double value) {
			if (value > 0 && value <= 100)
				return true;
			throw std::invalid_argument("value must be greater than 0 and not greater than 100");
		},
		"percentage"
	);
}

void pcom::setSheetWidth(PaintDataContainer * container) {
	setValue<double> (
		[&container]() { return container->getSheetWidth(); },
		[&container](double value) { container->setSheetWidth(value); },
		[](std::string line) { return std::stod(line); },
		[](double value) {
			if (value > 0)
				return true;
			throw std::invalid_argument("value must be greater than 0");
		},
		"sheet width"
	);
}

void pcom::setSheetLength(PaintDataContainer * container) {
	setValue<double> (
		[&container]() { return container->getSheetLength(); },
		[&container](double value) { container->setSheetLength(value); },
		[](std::string line) { return std::stod(line); },
		[](double value) {
			if (value > 0)
				return true;
			throw std::invalid_argument("value must be greater than 0");
		},
		"sheet length"
	);
}

void pcom::setCirculation(PaintDataContainer * container) {
	setValue<unsigned long> (
		[&container]() { return container->getCirculation(); },
		[&container](unsigned long value) { container->setCirculation(value); },
		[](std::string line) { return std::stoul(line); },
		[](unsigned long value) {
			if (value > 0)
				return true;
			throw std::invalid_argument("value must be greater than 0");
		},
		"circulation"
	);
}

void pcom::setPaintReserve(PaintDataContainer * container) {
	setValue<double> (
		[&container]() { return container->getPaintReserve(); },
		[&container](double value) { container->setPaintReserve(value); },
		[](std::string line) { return std::stod(line); },
		[](double value) {
			if (value > 0)
				return true;
			throw std::invalid_argument("value must be greater than 0");
		},
		"reserve of paint"
	);
}
