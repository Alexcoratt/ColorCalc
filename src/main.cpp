#include <iostream>
#include <algorithm>
#include <exception>
#include <functional>
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "IConnection.hpp"
#include "JsonConnection.hpp"
#include "PaintDataContainer.hpp"
#include "LacquerDataContainer.hpp"

#include "option_methods.hpp"

#include "IOption.hpp"
#include "BaseOptionContainer.hpp"
#include "CustomLeafOption.hpp"

#define PRESETS_FILE "data/standard_presets.json"
#define STRUCTURE_FILE "data/tables_structure.json"

namespace com = common_option_methods;
namespace pcom = paint_calculation_option_methods;
namespace lcom = lacquer_calculation_option_methods;

int main() {

	std::ifstream structureFile(STRUCTURE_FILE);
	std::fstream presetsFile(PRESETS_FILE);

	IConnection * conn = new JsonConnection(structureFile, presetsFile);
	std::cout << "Status: " << conn->getStatus() << std::endl;

	PaintDataContainer paintCalculationContainer(conn);

	CustomLeafOption<PaintDataContainer *> writePaintParametersOption(
		"write values of parameters",
		"Print current values of all paint calculation mode parameters",
		com::writeParameters,
		&paintCalculationContainer
	);

	CustomLeafOption<PaintDataContainer *> setPaintTypeOption(
		"set paint type",
		"Set type of paint you are going to use",
		pcom::setPaintType,
		&paintCalculationContainer);

	CustomLeafOption<PaintDataContainer *> setMaterialTypeOption(
		"set material type",
		"Set type of material you are going to use",
		pcom::setMaterialType,
		&paintCalculationContainer);

	CustomLeafOption<PaintDataContainer *> setPaintConsumptionOption(
		"set paint consumption",
		"Set paint consumption value manually (paint and material type settings clears if a user enters a new value)",
		pcom::setConsumption,
		&paintCalculationContainer
	);

	CustomLeafOption<PaintDataContainer *> setPaintDividerOption(
		"set divider",
		"Set divider of formula",
		pcom::setDivider,
		&paintCalculationContainer
	);

	CustomLeafOption<PaintDataContainer *> setPaintPercentageOption(
		"set printing percent",
		"Set percentage of sheet sealing",
		pcom::setPercentage,
		&paintCalculationContainer
	);

	CustomLeafOption<PaintDataContainer *> setPaintWidthOption(
		"set sheet width",
		"Set width value of the sheet",
		pcom::setSheetWidth,
		&paintCalculationContainer
	);

	CustomLeafOption<PaintDataContainer *> setPaintLengthOption(
		"set sheet width",
		"Set width value of the sheet",
		pcom::setSheetLength,
		&paintCalculationContainer
	);

	CustomLeafOption<PaintDataContainer *> setPaintCirculationOption(
		"set circulation",
		"set amount of edition",
		pcom::setCirculation,
		&paintCalculationContainer
	);

	CustomLeafOption<PaintDataContainer *> setPaintReserveOption(
		"set paint reserve",
		"set minimal amount of paint for an edition",
		pcom::setReserve,
		&paintCalculationContainer
	);

	CustomLeafOption<PaintDataContainer *> loadPaintCalculationPresetOption(
		"load preset",
		"load values of existing preset",
		pcom::loadPaintPreset,
		&paintCalculationContainer
	);

	CustomLeafOption<PaintDataContainer *> clearPaintCalculationValuesOption(
		"remove values",
		"Clears data from every paint calculation value",
		com::clearValues,
		&paintCalculationContainer
	);

	CustomLeafOption<PaintDataContainer *> calculatePaintAmountOption(
		"calculate amount of paint",
		"calculates required amount of paint based on other parameters",
		com::calculateResourceAmount,
		&paintCalculationContainer
	);

	BaseOptionContainer paintCalculation("paint calculation", "contains options to work with paint calculation data", {
		{'w', &writePaintParametersOption},
		{'p', &setPaintTypeOption},
		{'m', &setMaterialTypeOption},
		{'c', &setPaintConsumptionOption},
		{'d', &setPaintDividerOption},
		{'%', &setPaintPercentageOption},
		{'W', &setPaintWidthOption},
		{'L', &setPaintLengthOption},
		{'C', &setPaintCirculationOption},
		{'r', &setPaintReserveOption},
		{'l', &loadPaintCalculationPresetOption},
		{'R', &clearPaintCalculationValuesOption},
		{'a', &calculatePaintAmountOption},
	});

	LacquerDataContainer lacquerCalculationContainer(conn);

	CustomLeafOption<LacquerDataContainer *> writeLacquerParametersOption(
		"write values of parameters",
		"Print current values of all lacquer calculation mode parameters",
		com::writeParameters,
		&lacquerCalculationContainer
	);

	CustomLeafOption<LacquerDataContainer *> calculateLacquerAmountOption(
		"calculate amount of lacquer",
		"Calculates required amount of lacquer based on entered parameters",
		com::calculateResourceAmount,
		&lacquerCalculationContainer
	);

	CustomLeafOption<LacquerDataContainer *> loadLacquerCalculationPresetOption(
		"load lacquer calculation preset",
		"Loads values of selected preset into internal storage",
		lcom::loadLacquerPreset,
		&lacquerCalculationContainer
	);

	CustomLeafOption<LacquerDataContainer *> clearLacquerCalculationValuesOption(
		"remove lacquer calculation data",
		"Clears all entered lacquer calculation parameters",
		com::clearValues,
		&lacquerCalculationContainer
	);

	CustomLeafOption<LacquerDataContainer *> setLacquerPercentageOption(
		"set lacquer percentage",
		"Sets a percentage value of the lacquer coverage",
		lcom::setPercentage,
		&lacquerCalculationContainer
	);

	CustomLeafOption<LacquerDataContainer *> setLacquerConsumptionOption(
		"set lacquer consumption",
		"Sets a consumption value of the lacquer",
		lcom::setConsumption,
		&lacquerCalculationContainer
	);

	CustomLeafOption<LacquerDataContainer *> setLacquerSheetLengthOption(
		"set sheet length",
		"Sets a length value of the sheet",
		lcom::setSheetLength,
		&lacquerCalculationContainer
	);

	CustomLeafOption<LacquerDataContainer *> setLacquerSheetWidthOption(
		"set sheet width",
		"Sets a width value of the sheet",
		lcom::setSheetWidth,
		&lacquerCalculationContainer
	);

	CustomLeafOption<LacquerDataContainer *> setLacquerCirculationOption(
		"set circulation",
		"Sets a number of sheets",
		lcom::setCircualtion,
		&lacquerCalculationContainer
	);

	BaseOptionContainer lacquerCalculation("lacquer calculation", "contains options to work with lacquer calculation data", {
		{'w', &writeLacquerParametersOption},
		{'a', &calculateLacquerAmountOption},
		{'l', &loadLacquerCalculationPresetOption},
		{'R', &clearLacquerCalculationValuesOption},
		{'%', &setLacquerPercentageOption},
		{'c', &setLacquerConsumptionOption},
		{'L', &setLacquerSheetLengthOption},
		{'W', &setLacquerSheetWidthOption},
		{'C', &setLacquerCirculationOption}
	});

	BaseOptionContainer root("root", BASE_HELP_TEXT, {
		{'p', &paintCalculation},
		{'l', &lacquerCalculation}
	}, true);
	root.exec(0, std::cin, std::cout, "\n");

	delete conn;

	return 0;
}
