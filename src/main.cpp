#include <algorithm>
#include <exception>
#include <functional>
#include <iostream>
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

#define PAINT_CALCULATION_TABLE_NAME "расчет печатной краски"
#define LACQUER_CALCULATION_TABLE_NAME "расчет лака"

namespace pcom = paint_calculation_option_methods;
namespace com = common_option_methods;

int main() {

	std::ifstream file("../data/paint.json");
	IConnection * conn = new JsonConnection(file);

	PaintDataContainer paintCalculationContainer(conn);

	CustomLeafOption<PaintDataContainer *> writePaintParametersOption(
		"write values of parameters",
		"Print current values of all paint calculation mode parameters",
		com::writePaintParameters,
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
		pcom::setPaintConsumption,
		&paintCalculationContainer
	);

	CustomLeafOption<PaintDataContainer *> setDividerOption(
		"set divider",
		"Set divider of formula",
		pcom::setDivider,
		&paintCalculationContainer
	);

	CustomLeafOption<PaintDataContainer *> setPercentOption(
		"set printing percent",
		"Set percentage of sheet sealing",
		pcom::setPercentage,
		&paintCalculationContainer
	);

	CustomLeafOption<PaintDataContainer *> setWidthOption(
		"set sheet width",
		"Set width value of the sheet",
		pcom::setSheetWidth,
		&paintCalculationContainer
	);

	CustomLeafOption<PaintDataContainer *> setLengthOption(
		"set sheet width",
		"Set width value of the sheet",
		pcom::setSheetLength,
		&paintCalculationContainer
	);

	CustomLeafOption<PaintDataContainer *> setCirculationOption(
		"set circulation",
		"set amount of edition",
		pcom::setCirculation,
		&paintCalculationContainer
	);

	CustomLeafOption<PaintDataContainer *> setPaintReserveOption(
		"set paint reserve",
		"set minimal amount of paint for an edition",
		pcom::setPaintReserve,
		&paintCalculationContainer
	);

	CustomLeafOption<PaintDataContainer *> loadPaintCalculationPresetOption(
		"load preset",
		"load values of existing preset",
		com::loadPreset,
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
		{'d', &setDividerOption},
		{'%', &setPercentOption},
		{'W', &setWidthOption},
		{'L', &setLengthOption},
		{'C', &setCirculationOption},
		{'r', &setPaintReserveOption},
		{'l', &loadPaintCalculationPresetOption},
		{'R', &clearPaintCalculationValuesOption},
		{'a', &calculatePaintAmountOption}
	});

	LacquerDataContainer lacquerCalculationContainer(conn);

	CustomLeafOption<LacquerDataContainer *> writeLacquerParametersOption(
		"write values of parameters",
		"Print current values of all lacquer calculation mode parameters",
		com::writePaintParameters,
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
		com::loadPreset,
		&lacquerCalculationContainer
	);

	CustomLeafOption<LacquerDataContainer *> clearLacquerCalculationValuesOption(
		"remove lacquer calculation data",
		"Clears all entered lacquer calculation parameters",
		com::clearValues,
		&lacquerCalculationContainer
	);

	BaseOptionContainer lacquerCalculation("lacquer calculation", "contains options to work with lacquer calculation data", {
		{'w', &writeLacquerParametersOption},
		{'a', &calculateLacquerAmountOption},
		{'l', &loadLacquerCalculationPresetOption},
		{'R', &clearLacquerCalculationValuesOption}
	});

	BaseOptionContainer root("root", BASE_HELP_TEXT, {
		{'p', &paintCalculation},
		{'l', &lacquerCalculation}
	}, true);
	root.exec(0, std::cin, std::cout, "\n");

	delete conn;

	return 0;
}
