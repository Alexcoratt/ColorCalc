#include <cstddef>
#include <exception>
#include <stdexcept>
#include <iostream>
#include <string>
#include <vector>
#include <functional>

#include "DefaultOptionIsChosenExcepion.hpp"
#include <PaintDataManager.hpp>
#include <IDataManager.hpp>
#include "UndefinedValueException.hpp"
#include "option_methods.hpp"

namespace com = common_option_methods;
namespace pcom = paint_calculation_option_methods;
namespace lcom = lacquer_calculation_option_methods;
namespace fcom = foil_calculation_option_methods;
namespace from = foil_rolls_option_methods;

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
		if (!line.size())
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
	if (variants.size() == 0) {
		std::cout << "No available variants\n";
		throw DefaultOptionIsChosenException();
	}
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

void setVariant(std::vector<std::string> const & variants, std::function<std::string()> get, std::function<void(std::string)> set) {
	std::string prompt;
	AutoValue defaultVariant;
	try {
		defaultVariant = (unsigned long)getIndex(variants, get());
	} catch (std::invalid_argument const &) {
		defaultVariant.clear();
	} catch (UndefinedValueException const &) {
		defaultVariant.clear();
	}

	if (defaultVariant.isNull())
		prompt = "Enter index of the variant (default=undefined): ";
	else
		prompt = "Enter index of the variant (default=" + std::to_string((unsigned long)defaultVariant + 1) + "): ";

	set(variants[readVariant(prompt, variants)]);
}

void com::clearValues(IDataManager * manager) {
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
		manager->clear();
		std::cout << "Submitted" << std::endl << "Fields are cleared" << std::endl;
	} else
		std::cout << "Aborted" << std::endl;
}

void com::calculateResourceAmount(IDataManager const * manager) {
	double res = manager->calculate();
	std::cout << "Required amount equals " << res << "kg" << std::endl;
}

void com::writeParameters(IDataManager const * manager) {
	try {
		auto presetName = manager->getName();
		std::cout << "Preset name:\t" << presetName << std::endl << std::endl;
	} catch (UndefinedValueException const &) {}

	auto params = manager->exportData();
	for (auto iter = params.begin(); iter != params.end(); ++iter)
		std::cout << iter->first << ":\t" << iter->second << std::endl;
}

void com::loadPreset(IDataManager * manager) {
	std::vector<std::string> presets = manager->getConnection()->getPresetNames();

	std::cout << "Select the preset to load" << std::endl;
	try {
		setVariant(
			presets,
			[&]() { return manager->getName(); },
			[&](std::string name) { manager->loadPreset(name); }
		);
	} catch (DefaultOptionIsChosenException const &) {}

	std::cout << "Preset ";
	try {
		std::string presetName = manager->getName();
		std::cout << "named \"" << presetName << "\" is loaded" << std::endl;
	} catch (UndefinedValueException const &) {
		std::cout << "is undefined" << std::endl;
	}
}

void com::createPreset(IDataManager * manager) {
	std::cout << "Enter name of the new preset (leave field empty to abort operation)" << std::endl;

	try {
		std::string name = readValue<std::string>(
			"Enter name (default=abort): ",
			[](std::string line) { return line; }
		);
		manager->createPreset(name);
	} catch (DefaultOptionIsChosenException const &) {
		std::cout << "Aborted" << std::endl;
	}
}

void com::updatePreset(IDataManager * manager) {
	std::vector<std::string> presets = manager->getConnection()->getPresetNames();

	std::cout << "Select name of the preset you want to update (leave field empty to abort operation)" << std::endl;
	std::string presetName;

	try {
		setVariant(
			presets,
			[]() { return "abort"; },
			[&](std::string name) {
				manager->updatePreset(name);
				presetName = name;
			}
		);
	} catch (DefaultOptionIsChosenException const &) {
		std::cout << "Aborted" << std::endl;
	}
}

void com::removePreset(IDataManager * manager) {
	std::vector<std::string> presets = manager->getConnection()->getPresetNames();

	std::cout << "Select name of the paint calculation preset you want to remove (leave field empty to abort operation)" << std::endl;
	std::string presetName;

	try {
		setVariant(
			presets,
			[]() { return "abort"; },
			[&](std::string name) {
				manager->removePreset(name);
				presetName = name;
			}
		);
	} catch (DefaultOptionIsChosenException const &) {
		std::cout << "Aborted" << std::endl;
	}
}

void pcom::setPaintType(PaintDataManager * manager) {
	std::cout << "Select paint type" << std::endl;
	try {
		setVariant(
			manager->getPaintTypes(),
			[&]() { return manager->getPaintType(); },
			[&](std::string type) { manager->setPaintType(type); }
		);
	} catch (DefaultOptionIsChosenException const &) {}

	std::cout << "Paint type ";
	try {
		std::string type = manager->getPaintType();
		std::cout << "\"" << type << "\" is set" << std::endl;
	} catch (UndefinedValueException const &) {
		std::cout << "is undefined" << std::endl;
	}
}

void pcom::setMaterialType(PaintDataManager * manager) {
	std::cout << "Select material type" << std::endl;
	try {
		setVariant(
			manager->getMaterialTypes(),
			[&]() { return manager->getMaterialType(); },
			[&](std::string type) { manager->setMaterialType(type); }
		);
	} catch (DefaultOptionIsChosenException const &) {}

	std::cout << "Material type ";
	try {
		std::string type = manager->getMaterialType();
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

void pcom::setConsumption(PaintDataManager * manager) {
	std::cout << "Set paint consumption value" << std::endl;

	setValue<double> (
		[&]() { return manager->getPaintConsumption(); },
		[&](double value) { manager->setPaintConsumption(value); },
		[](std::string line) { return std::stod(line); },
		[](double value) {
			if (value > 0)
				return true;
			throw std::invalid_argument("value must be greater than 0");
		}
	);

	std::cout << "Paint consumption ";
	try {
		auto paintConsumption = manager->getPaintConsumption();
		std::cout << "value " << paintConsumption << " is set" << std::endl;
	} catch (UndefinedValueException const &) {
		std::cout << "is undefined" << std::endl;
	}
}

void pcom::setDivider(PaintDataManager * manager) {
	std::cout << "Set divider value" << std::endl;

	setValue<double> (
		[&]() { return manager->getDivider(); },
		[&](double value) { manager->setDivider(value); },
		[](std::string line) { return std::stod(line); },
		[](double value) {
			if (value > 0)
				return true;
			throw std::invalid_argument("value must be greater than 0");
		}
	);

	std::cout << "Divider ";
	try {
		auto divider = manager->getDivider();
		std::cout << "value " << divider << " is set" << std::endl;
	} catch (UndefinedValueException const &) {
		std::cout << "is undefined" << std::endl;
	}
}

void pcom::setPercentage(PaintDataManager * manager) {
	std::cout << "Set percentage value" << std::endl;

	setValue<double> (
		[&]() { return manager->getPercentage(); },
		[&](double value) { manager->setPercentage(value); },
		[](std::string line) { return std::stod(line); },
		[](double value) {
			if (value > 0 && value <= 100)
				return true;
			throw std::invalid_argument("value must be greater than 0 and not greater than 100");
		}
	);

	std::cout << "Percentage ";
	try {
		auto percentage = manager->getPercentage();
		std::cout << "value " << percentage << " is set" << std::endl;
	} catch (UndefinedValueException const &) {
		std::cout << "is undefined" << std::endl;
	}
}

void pcom::setSheetWidth(PaintDataManager * manager) {
	std::cout << "Set sheet width value" << std::endl;

	setValue<double> (
		[&]() { return manager->getSheetWidth(); },
		[&](double value) { manager->setSheetWidth(value); },
		[](std::string line) { return std::stod(line); },
		[](double value) {
			if (value > 0)
				return true;
			throw std::invalid_argument("value must be greater than 0");
		}
	);

	std::cout << "Sheet width ";
	try {
		auto sheetWidth = manager->getSheetWidth();
		std::cout << "value " << sheetWidth << " is set" << std::endl;
	} catch (UndefinedValueException const &) {
		std::cout << "is undefined" << std::endl;
	}
}

void pcom::setSheetLength(PaintDataManager * manager) {
	std::cout << "Set sheet length value" << std::endl;

	setValue<double> (
		[&]() { return manager->getSheetLength(); },
		[&](double value) { manager->setSheetLength(value); },
		[](std::string line) { return std::stod(line); },
		[](double value) {
			if (value > 0)
				return true;
			throw std::invalid_argument("value must be greater than 0");
		}
	);

	std::cout << "Sheet length ";
	try {
		auto sheetLength = manager->getSheetLength();
		std::cout << "value " << sheetLength << " is set" << std::endl;
	} catch (UndefinedValueException const &) {
		std::cout << "is undefined" << std::endl;
	}
}

void pcom::setCirculation(PaintDataManager * manager) {
	std::cout << "Set circulation value" << std::endl;

	setValue<unsigned long> (
		[&]() { return manager->getCirculation(); },
		[&](unsigned long value) { manager->setCirculation(value); },
		[](std::string line) { return std::stoul(line); },
		[](unsigned long value) {
			if (value > 0)
				return true;
			throw std::invalid_argument("value must be greater than 0");
		}
	);

	std::cout << "Circulation ";
	try {
		auto circulation = manager->getCirculation();
		std::cout << "value " << circulation << " is set" << std::endl;
	} catch (UndefinedValueException const &) {
		std::cout << "is undefined" << std::endl;
	}
}

void pcom::setReserve(PaintDataManager * manager) {
	std::cout << "Set paint reserve value" << std::endl;

	setValue<double>(
		[&]() { return manager->getPaintReserve(); },
		[&](double value) { manager->setPaintReserve(value); },
		[](std::string line) { return std::stod(line); },
		[](double value) {
			if (value > 0)
				return true;
			throw std::invalid_argument("value must be greater than 0");
		}
	);

	std::cout << "Paint reserve ";
	try {
		auto paintReserve = manager->getPaintReserve();
		std::cout << "value " << paintReserve << " is set" << std::endl;
	} catch (UndefinedValueException const &) {
		std::cout << "is undefined" << std::endl;
	}
}


void lcom::setPercentage(LacquerDataManager * manager) {
	std::cout << "Set percentage of lacquer coverage" << std::endl;

	setValue<double>(
		[&]() { return manager->getPercentage(); },
		[&](double value) { manager->setPercentage(value); },
		[](std::string line) { return std::stod(line); },
		[](double value) {
			if (value > 0 && value <= 100)
				return true;
			throw std::invalid_argument("value must be greater than 0 and not greater than 100");
		}
	);

	std::cout << "Lacquer coverage percentage ";
	try {
		auto value = manager->getPercentage();
		std::cout << "value " << value << " is set" << std::endl;
	} catch (UndefinedValueException const &) {
		std::cout << "is undefined" << std::endl;
	}
}

void lcom::setConsumption(LacquerDataManager * manager) {
	std::cout << "Set consumption of lacquer" << std::endl;

	setValue<double>(
		[&]() { return manager->getLacquerConsumption(); },
		[&](double value) { manager->setLacquerConsumption(value); },
		[](std::string line) { return std::stod(line); },
		[](double value) {
			if (value > 0)
				return true;
			throw std::invalid_argument("value must be greater than 0");
		}
	);

	std::cout << "Lacquer consumption ";
	try {
		auto value = manager->getLacquerConsumption();
		std::cout << "value " << value << " is set" << std::endl;
	} catch (UndefinedValueException const &) {
		std::cout << "is undefined" << std::endl;
	}
}

void lcom::setSheetLength(LacquerDataManager * manager) {
	std::cout << "Set length of the sheet" << std::endl;

	setValue<double>(
		[&]() { return manager->getSheetLength(); },
		[&](double value) { manager->setSheetLength(value); },
		[](std::string line) { return std::stod(line); },
		[](double value) {
			if (value > 0)
				return true;
			throw std::invalid_argument("value must be greater than 0");
		}
	);

	std::cout << "Length of the sheet ";
	try {
		auto value = manager->getSheetLength();
		std::cout << "value " << value << " is set" << std::endl;
	} catch (UndefinedValueException const &) {
		std::cout << "is undefined" << std::endl;
	}
}

void lcom::setSheetWidth(LacquerDataManager * manager) {
	std::cout << "Set width of the sheet" << std::endl;

	setValue<double>(
		[&]() { return manager->getSheetWidth(); },
		[&](double value) { manager->setSheetWidth(value); },
		[](std::string line) { return std::stod(line); },
		[](double value) {
			if (value > 0)
				return true;
			throw std::invalid_argument("value must be greater than 0");
		}
	);

	std::cout << "Width of the sheet ";
	try {
		auto value = manager->getSheetWidth();
		std::cout << "value " << value << " is set" << std::endl;
	} catch (UndefinedValueException const &) {
		std::cout << "is undefined" << std::endl;
	}
}

void lcom::setCircualtion(LacquerDataManager * manager) {
	std::cout << "Set circulation" << std::endl;

	setValue<std::size_t>(
		[&]() { return manager->getCirculation(); },
		[&](std::size_t value) { manager->setCirculation(value); },
		[](std::string line) { return std::stoul(line); },
		[](std::size_t value) {
			if (value > 0)
				return true;
			throw std::invalid_argument("value must be greater than 0");
		}
	);

	std::cout << "Circulation ";
	try {
		auto value = manager->getCirculation();
		std::cout << "value " << value << " is set" << std::endl;
	} catch (UndefinedValueException const &) {
		std::cout << "is undefined" << std::endl;
	}
}


void fcom::setCirulation(FoilDataManager * manager) {
	std::cout << "Set circulation" << std::endl;

	setValue<std::size_t>(
		[&]() { return manager->getCirculation(); },
		[&](std::size_t value) { manager->setCirculation(value); },
		[](std::string line) { return std::stoul(line); },
		[](std::size_t value) {
			if (value > 0)
				return true;
			throw std::invalid_argument("value must be greater than 0");
		}
	);

	std::cout << "Circulation ";
	try {
		auto value = manager->getCirculation();
		std::cout << "value " << value << " is set" << std::endl;
	} catch (UndefinedValueException const &) {
		std::cout << "is undefined" << std::endl;
	}
}

void fcom::setLength(FoilDataManager * manager) {
	std::cout << "Set length of the roll" << std::endl;

	setValue<double>(
		[&]() { return manager->getLength(); },
		[&](double value) { manager->setLength(value); },
		[](std::string line) { return std::stod(line); },
		[](double value) {
			if (value > 0)
				return true;
			throw std::invalid_argument("value must be greater than 0");
		}
	);

	std::cout << "Length of the roll ";
	try {
		auto value = manager->getLength();
		std::cout << "value " << value << " is set" << std::endl;
	} catch (UndefinedValueException const &) {
		std::cout << "is undefined" << std::endl;
	}
}

void fcom::setWidth(FoilDataManager * manager) {
	std::cout << "Set width of the roll" << std::endl;

	setValue<double>(
		[&]() { return manager->getWidth(); },
		[&](double value) { manager->setWidth(value); },
		[](std::string line) { return std::stod(line); },
		[](double value) {
			if (value > 0)
				return true;
			throw std::invalid_argument("value must be greater than 0");
		}
	);

	std::cout << "Width of the roll ";
	try {
		auto value = manager->getWidth();
		std::cout << "value " << value << " is set" << std::endl;
	} catch (UndefinedValueException const &) {
		std::cout << "is undefined" << std::endl;
	}
}

void fcom::setSheetNumber(FoilDataManager * manager) {
	std::cout << "Set number of sheets" << std::endl;

	setValue<std::size_t>(
		[&]() { return manager->getSheetNumber(); },
		[&](std::size_t value) { manager->setSheetNumber(value); },
		[](std::string line) { return std::stoul(line); },
		[](std::size_t value) {
			if (value > 0)
				return true;
			throw std::invalid_argument("value must be greater than 0");
		}
	);

	std::cout << "Number of sheets ";
	try {
		auto value = manager->getSheetNumber();
		std::cout << "value " << value << " is set" << std::endl;
	} catch (UndefinedValueException const &) {
		std::cout << "is undefined" << std::endl;
	}
}

void fcom::setLengthReserve(FoilDataManager * manager) {
	std::cout << "Set length reserve of the roll" << std::endl;

	setValue<double>(
		[&]() { return manager->getLengthReserve(); },
		[&](double value) { manager->setLengthReserve(value); },
		[](std::string line) { return std::stod(line); },
		[](double value) {
			if (value > 0)
				return true;
			throw std::invalid_argument("value must be greater than 0");
		}
	);

	std::cout << "Length reserve of the roll ";
	try {
		auto value = manager->getLengthReserve();
		std::cout << "value " << value << " is set" << std::endl;
	} catch (UndefinedValueException const &) {
		std::cout << "is undefined" << std::endl;
	}
}

void fcom::setWidthReserve(FoilDataManager * manager) {
	std::cout << "Set width reserve of the roll" << std::endl;

	setValue<double>(
		[&]() { return manager->getWidthReserve(); },
		[&](double value) { manager->setWidthReserve(value); },
		[](std::string line) { return std::stod(line); },
		[](double value) {
			if (value > 0)
				return true;
			throw std::invalid_argument("value must be greater than 0");
		}
	);

	std::cout << "Width reserve of the roll ";
	try {
		auto value = manager->getWidthReserve();
		std::cout << "value " << value << " is set" << std::endl;
	} catch (UndefinedValueException const &) {
		std::cout << "is undefined" << std::endl;
	}
}

void fcom::calculateFoilRollLength(FoilDataManager const * manager) {
	double length = manager->calculate();
	std::cout << "Required roller's length equals " << length << "m" << std::endl;
}

void fcom::writeSuitableRolls(FoilDataManager const * manager) {
	auto rollNames = manager->getSuitableFoilRolls();
	if (rollNames.size() == 0) {
		std::cout << "No suitable rolls found\n";
		return;
	}

	std::cout << "Suitable rolls are:\n";
	for (auto rollName : rollNames)
		std::cout << rollName << '\n';
}


void from::setLength(FoilRollsDataManager * manager) {
	std::cout << "Set length of the roll" << std::endl;

	setValue<double>(
		[&]() { return manager->getLength(); },
		[&](double value) { manager->setLength(value); },
		[](std::string line) { return std::stod(line); },
		[](double value) {
			if (value > 0)
				return true;
			throw std::invalid_argument("value must be greater than 0");
		}
	);

	std::cout << "Width reserve of the roll ";
	try {
		auto value = manager->getLength();
		std::cout << "value " << value << " is set" << std::endl;
	} catch (UndefinedValueException const &) {
		std::cout << "is undefined" << std::endl;
	}
}

void from::setWidth(FoilRollsDataManager * manager) {
	std::cout << "Set width of the roll" << std::endl;

	setValue<double>(
		[&]() { return manager->getWidth(); },
		[&](double value) { manager->setWidth(value); },
		[](std::string line) { return std::stod(line); },
		[](double value) {
			if (value > 0)
				return true;
			throw std::invalid_argument("value must be greater than 0");
		}
	);

	std::cout << "Width reserve of the roll ";
	try {
		auto value = manager->getWidth();
		std::cout << "value " << value << " is set" << std::endl;
	} catch (UndefinedValueException const &) {
		std::cout << "is undefined" << std::endl;
	}
}
