#include <iostream>
#include <exception>
#include <functional>
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>

#include <IConnection.hpp>
#include <JsonConnection.hpp>
#include <PaintDataDispatcher.hpp>
#include <LacquerDataDispatcher.hpp>
#include <FoilDataDispatcher.hpp>
#include <FoilRollsDataDispatcher.hpp>

#include <option_methods.hpp>

#include <IOption.hpp>
#include <BaseOptionContainer.hpp>
#include <CustomLeafOption.hpp>

#define STRUCTURE_FILE "data/tables_structure.json"
#define STANDARD_PRESETS_FILE "data/standard_presets.json"
#define USER_PRESETS_FILE "data/user_presets.json"

namespace com = common_option_methods;
namespace pcom = paint_calculation_option_methods;
namespace lcom = lacquer_calculation_option_methods;
namespace fcom = foil_calculation_option_methods;
namespace from = foil_rolls_option_methods;

int main() {
	IConnection * conn = new JsonConnection(STRUCTURE_FILE, STANDARD_PRESETS_FILE);
	IConnection * userConn = new JsonConnection(STRUCTURE_FILE, USER_PRESETS_FILE, false);

	PaintDataDispatcher paintCalculationDispatcher(userConn);

	CustomLeafOption<PaintDataDispatcher *> writePaintParametersOption(
		"write values of parameters",
		"Print current values of all paint calculation mode parameters",
		com::writeParameters,
		&paintCalculationDispatcher
	);

	CustomLeafOption<PaintDataDispatcher *> setPaintTypeOption(
		"set paint type",
		"Set type of paint you are going to use",
		pcom::setPaintType,
		&paintCalculationDispatcher);

	CustomLeafOption<PaintDataDispatcher *> setMaterialTypeOption(
		"set material type",
		"Set type of material you are going to use",
		pcom::setMaterialType,
		&paintCalculationDispatcher);

	CustomLeafOption<PaintDataDispatcher *> setPaintConsumptionOption(
		"set paint consumption",
		"Set paint consumption value manually (paint and material type settings clears if a user enters a new value)",
		pcom::setConsumption,
		&paintCalculationDispatcher
	);

	CustomLeafOption<PaintDataDispatcher *> setPaintDividerOption(
		"set divider",
		"Set divider of formula",
		pcom::setDivider,
		&paintCalculationDispatcher
	);

	CustomLeafOption<PaintDataDispatcher *> setPaintPercentageOption(
		"set printing percent",
		"Set percentage of sheet sealing",
		pcom::setPercentage,
		&paintCalculationDispatcher
	);

	CustomLeafOption<PaintDataDispatcher *> setPaintWidthOption(
		"set sheet width",
		"Set width value of the sheet",
		pcom::setSheetWidth,
		&paintCalculationDispatcher
	);

	CustomLeafOption<PaintDataDispatcher *> setPaintLengthOption(
		"set sheet width",
		"Set width value of the sheet",
		pcom::setSheetLength,
		&paintCalculationDispatcher
	);

	CustomLeafOption<PaintDataDispatcher *> setPaintCirculationOption(
		"set circulation",
		"set amount of edition",
		pcom::setCirculation,
		&paintCalculationDispatcher
	);

	CustomLeafOption<PaintDataDispatcher *> setPaintReserveOption(
		"set paint reserve",
		"set minimal amount of paint for an edition",
		pcom::setReserve,
		&paintCalculationDispatcher
	);

	CustomLeafOption<PaintDataDispatcher *> loadPaintCalculationPresetOption(
		"load preset",
		"load values of existing preset",
		com::loadPreset,
		&paintCalculationDispatcher
	);

	CustomLeafOption<PaintDataDispatcher *> clearPaintCalculationValuesOption(
		"remove values",
		"Clears data from every paint calculation value",
		com::clearValues,
		&paintCalculationDispatcher
	);

	CustomLeafOption<PaintDataDispatcher *> calculatePaintAmountOption(
		"calculate amount of paint",
		"Calculates required amount of paint based on other parameters",
		com::calculateResourceAmount,
		&paintCalculationDispatcher
	);

	CustomLeafOption<PaintDataDispatcher *> createPaintPresetOption(
		"create paint calculation preset",
		"Creates a new paint calculation preset based on entered values",
		com::createPreset,
		&paintCalculationDispatcher
	);

	CustomLeafOption<PaintDataDispatcher *> updatePaintPresetOption(
		"update paint calculation preset",
		"Updated data in an existing paint calculation preset",
		com::updatePreset,
		&paintCalculationDispatcher
	);

	CustomLeafOption<PaintDataDispatcher *> removePaintPresetOption(
		"remove paint calculation preset",
		"Removes an existing paint calculation preset",
		com::removePreset,
		&paintCalculationDispatcher
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
		{'+', &createPaintPresetOption},
		{'/', &updatePaintPresetOption},
		{'-', &removePaintPresetOption}
	});

	LacquerDataDispatcher lacquerCalculationDispatcher(conn);

	CustomLeafOption<LacquerDataDispatcher *> writeLacquerParametersOption(
		"write values of parameters",
		"Print current values of all lacquer calculation mode parameters",
		com::writeParameters,
		&lacquerCalculationDispatcher
	);

	CustomLeafOption<LacquerDataDispatcher *> calculateLacquerAmountOption(
		"calculate amount of lacquer",
		"Calculates required amount of lacquer based on entered parameters",
		com::calculateResourceAmount,
		&lacquerCalculationDispatcher
	);

	CustomLeafOption<LacquerDataDispatcher *> loadLacquerCalculationPresetOption(
		"load lacquer calculation preset",
		"Loads values of selected preset into internal storage",
		com::loadPreset,
		&lacquerCalculationDispatcher
	);

	CustomLeafOption<LacquerDataDispatcher *> clearLacquerCalculationValuesOption(
		"remove lacquer calculation data",
		"Clears all entered lacquer calculation parameters",
		com::clearValues,
		&lacquerCalculationDispatcher
	);

	CustomLeafOption<LacquerDataDispatcher *> setLacquerPercentageOption(
		"set lacquer percentage",
		"Sets a percentage value of the lacquer coverage",
		lcom::setPercentage,
		&lacquerCalculationDispatcher
	);

	CustomLeafOption<LacquerDataDispatcher *> setLacquerConsumptionOption(
		"set lacquer consumption",
		"Sets a consumption value of the lacquer",
		lcom::setConsumption,
		&lacquerCalculationDispatcher
	);

	CustomLeafOption<LacquerDataDispatcher *> setLacquerSheetLengthOption(
		"set sheet length",
		"Sets a length value of the sheet",
		lcom::setSheetLength,
		&lacquerCalculationDispatcher
	);

	CustomLeafOption<LacquerDataDispatcher *> setLacquerSheetWidthOption(
		"set sheet width",
		"Sets a width value of the sheet",
		lcom::setSheetWidth,
		&lacquerCalculationDispatcher
	);

	CustomLeafOption<LacquerDataDispatcher *> setLacquerCirculationOption(
		"set circulation",
		"Sets a number of sheets",
		lcom::setCircualtion,
		&lacquerCalculationDispatcher
	);

	CustomLeafOption<LacquerDataDispatcher *> createLacquerPresetOption(
		"create lacquer preset",
		"Creates a new lacquer calculation preset",
		com::createPreset,
		&lacquerCalculationDispatcher
	);

	CustomLeafOption<LacquerDataDispatcher *> updateLacquerPresetOption(
		"update lacquer preset",
		"Updates the selected lacquer calculation preset",
		com::updatePreset,
		&lacquerCalculationDispatcher
	);

	CustomLeafOption<LacquerDataDispatcher *> removeLacquerPresetOption(
		"remove lacquer preset",
		"Removes the selected lacquer calculation preset",
		com::removePreset,
		&lacquerCalculationDispatcher
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
		{'C', &setLacquerCirculationOption},
		{'+', &createLacquerPresetOption},
		{'/', &updateLacquerPresetOption},
		{'-', &removeLacquerPresetOption}
	});

	FoilDataDispatcher foilDataDispatcher(conn);

	CustomLeafOption<FoilDataDispatcher *> setFoilCirculationOption(
		"set circulation",
		"Sets quantity of the edition",
		fcom::setCirulation,
		&foilDataDispatcher
	);

	CustomLeafOption<FoilDataDispatcher *> setFoilStampLengthOption(
		"set length",
		"Sets length of the stamp",
		fcom::setLength,
		&foilDataDispatcher
	);

	CustomLeafOption<FoilDataDispatcher *> setFoilStampWidthOption(
		"set width",
		"Sets width of the stamp",
		fcom::setWidth,
		&foilDataDispatcher
	);

	CustomLeafOption<FoilDataDispatcher *> setFoilSheetNumberOption(
		"set sheet number",
		"Sets the number of sheets to be printed with one part of the foil",
		fcom::setSheetNumber,
		&foilDataDispatcher
	);

	CustomLeafOption<FoilDataDispatcher *> setFoilLengthReserveOption(
		"set length reserve",
		"Sets reserve value of length of the foil roller",
		fcom::setLengthReserve,
		&foilDataDispatcher
	);

	CustomLeafOption<FoilDataDispatcher *> setFoilWidthReserveOption(
		"set width reserve",
		"Sets reserve value of width of the foil roller",
		fcom::setWidthReserve,
		&foilDataDispatcher
	);

	CustomLeafOption<FoilDataDispatcher *> loadFoilPresetOption(
		"load foil calculation preset",
		"Loads the selected foil calculation preset",
		com::loadPreset,
		&foilDataDispatcher
	);

	CustomLeafOption<FoilDataDispatcher *> writeFoilParametersOption(
		"write parameters",
		"Writes entered foil calculation parameters",
		com::writeParameters,
		&foilDataDispatcher
	);

	CustomLeafOption<FoilDataDispatcher *> calculateFoilLengthOption(
		"calculate foil length",
		"Calculates length of the foil roll",
		fcom::calculateFoilRollLength,
		&foilDataDispatcher
	);

	CustomLeafOption<FoilDataDispatcher *> writeSuitableFoilRollsOption(
		"write suitable rolls",
		"Writes the most suitable rolls of foil in descending order",
		fcom::writeSuitableRolls,
		&foilDataDispatcher
	);

	CustomLeafOption<FoilDataDispatcher *> createFoilPresetOption(
		"create foil preset",
		"Creates the new foil calculation preset",
		com::createPreset,
		&foilDataDispatcher
	);

	CustomLeafOption<FoilDataDispatcher *> updateFoilPresetOption(
		"update foil preset",
		"Updates the selected foil calculation preset",
		com::updatePreset,
		&foilDataDispatcher
	);

	CustomLeafOption<FoilDataDispatcher *> removeFoilPresetOption(
		"remove foil preset",
		"Removes the selected foil calculation preset",
		com::removePreset,
		&foilDataDispatcher
	);

	CustomLeafOption<FoilDataDispatcher *> clearFoilDataOption(
		"clears data",
		"Clears all foil calculation params",
		com::clearValues,
		&foilDataDispatcher
	);

	BaseOptionContainer foilCalculation("foil calculation", "Contains methods to perform foil calculations", {
		{'C', &setFoilCirculationOption},
		{'L', &setFoilStampLengthOption},
		{'W', &setFoilStampWidthOption},
		{'n', &setFoilSheetNumberOption},
		{'e', &setFoilLengthReserveOption},
		{'i', &setFoilWidthReserveOption},
		{'l', &loadFoilPresetOption},
		{'w', &writeFoilParametersOption},
		{'a', &calculateFoilLengthOption},
		{'s', &writeSuitableFoilRollsOption},
		{'+', &createFoilPresetOption},
		{'/', &updateFoilPresetOption},
		{'-', &removeFoilPresetOption},
		{'R', &clearFoilDataOption}
	});


	FoilRollsDataDispatcher foilRollsDataDispatcher(conn);

	CustomLeafOption<FoilRollsDataDispatcher *> setFoilRollLengthOption(
		"set roll length",
		"Sets the length of the roll",
		from::setLength,
		&foilRollsDataDispatcher
	);

	CustomLeafOption<FoilRollsDataDispatcher *> setFoilRollWidthOption(
		"set roll width",
		"Sets the width of the roll",
		from::setWidth,
		&foilRollsDataDispatcher
	);

	CustomLeafOption<FoilRollsDataDispatcher *> loadFoilRollsPresetOption(
		"load foil roll preset",
		"Loads preset containing data about a roll of foil",
		com::loadPreset,
		&foilRollsDataDispatcher
	);

	CustomLeafOption<FoilRollsDataDispatcher *> createFoilRollsPresetOption(
		"create foil roll preset",
		"Creates a new preset containing data about a roll of foil",
		com::createPreset,
		&foilRollsDataDispatcher
	);

	CustomLeafOption<FoilRollsDataDispatcher *> updateFoilRollsPresetOption(
		"update foil roll preset",
		"Updates the selected foil roll preset with previously entered params",
		com::updatePreset,
		&foilRollsDataDispatcher
	);

	CustomLeafOption<FoilRollsDataDispatcher *> removeFoilRollsPresetOption(
		"remove foil roll preset",
		"Removes the selected foil roll preset",
		com::updatePreset,
		&foilRollsDataDispatcher
	);

	CustomLeafOption<FoilRollsDataDispatcher *> writeFoilRollsDispatcherParams(
		"write parameters",
		"Writes entered parameters",
		com::writeParameters,
		&foilRollsDataDispatcher
	);

	BaseOptionContainer foilRolls("foil rolls", "Contains methods to manipulate data about foil rolls being used", {
		{'L', &setFoilRollLengthOption},
		{'W', &setFoilRollWidthOption},
		{'l', &loadFoilRollsPresetOption},
		{'w', &writeFoilRollsDispatcherParams},
		{'+', &createFoilRollsPresetOption},
		{'/', &updateFoilRollsPresetOption},
		{'-', &removeFoilRollsPresetOption}
	});

	BaseOptionContainer root("root", BASE_HELP_TEXT, {
		{'p', &paintCalculation},
		{'l', &lacquerCalculation},
		{'f', &foilCalculation},
		{'r', &foilRolls}
	}, true);
	root.exec(nullptr, std::cin, std::cout, "\n");

	delete conn;
	delete userConn;

	return 0;
}
