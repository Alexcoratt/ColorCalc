#include <iostream>
#include <exception>
#include <functional>
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>

#include <ITableConnection.hpp>
#include <JSONTableConnection.hpp>
#include <TableConnectionManager.hpp>

#include <PaintDataManager.hpp>
#include <LacquerDataManager.hpp>
#include <FoilDataManager.hpp>
#include <FoilRollsDataManager.hpp>
#include <PaintConsumptionDataManager.hpp>

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
	ITableConnection * standardPaintConn = new JSONTableConnection(STRUCTURE_FILE, STANDARD_PRESETS_FILE, "paint_calculation");
	ITableConnection * userPaintConn = new JSONTableConnection(STRUCTURE_FILE, USER_PRESETS_FILE, "paint_calculation", false);
	ITableConnection * paintConn = new TableConnectionManager{{standardPaintConn, userPaintConn}};

	ITableConnection * paintConsumptionConn = new JSONTableConnection(STRUCTURE_FILE, STANDARD_PRESETS_FILE, "paint_consumption");

	PaintConsumptionDataManager paintConsumptionManager(paintConsumptionConn);
	PaintDataManager paintCalculationManager(paintConn, &paintConsumptionManager);

	CustomLeafOption<PaintDataManager *> writePaintParametersOption(
		"write values of parameters",
		"Print current values of all paint calculation mode parameters",
		com::writeParameters,
		&paintCalculationManager
	);

	CustomLeafOption<PaintDataManager *> setPaintTypeOption(
		"set paint type",
		"Set type of paint you are going to use",
		pcom::setPaintType,
		&paintCalculationManager
	);

	CustomLeafOption<PaintDataManager *> setMaterialTypeOption(
		"set material type",
		"Set type of material you are going to use",
		pcom::setMaterialType,
		&paintCalculationManager
	);

	CustomLeafOption<PaintDataManager *> setPaintConsumptionOption(
		"set paint consumption",
		"Set paint consumption value manually (paint and material type settings clears if a user enters a new value)",
		pcom::setConsumption,
		&paintCalculationManager
	);

	CustomLeafOption<PaintDataManager *> setPaintDividerOption(
		"set divider",
		"Set divider of formula",
		pcom::setDivider,
		&paintCalculationManager
	);

	CustomLeafOption<PaintDataManager *> setPaintPercentageOption(
		"set printing percent",
		"Set percentage of sheet sealing",
		pcom::setPercentage,
		&paintCalculationManager
	);

	CustomLeafOption<PaintDataManager *> setPaintWidthOption(
		"set sheet width",
		"Set width value of the sheet",
		pcom::setSheetWidth,
		&paintCalculationManager
	);

	CustomLeafOption<PaintDataManager *> setPaintLengthOption(
		"set sheet width",
		"Set width value of the sheet",
		pcom::setSheetLength,
		&paintCalculationManager
	);

	CustomLeafOption<PaintDataManager *> setPaintCirculationOption(
		"set circulation",
		"set amount of edition",
		pcom::setCirculation,
		&paintCalculationManager
	);

	CustomLeafOption<PaintDataManager *> setPaintReserveOption(
		"set paint reserve",
		"set minimal amount of paint for an edition",
		pcom::setReserve,
		&paintCalculationManager
	);

	CustomLeafOption<PaintDataManager *> loadPaintCalculationPresetOption(
		"load preset",
		"load values of existing preset",
		com::loadPreset,
		&paintCalculationManager
	);

	CustomLeafOption<PaintDataManager *> clearPaintCalculationValuesOption(
		"remove values",
		"Clears data from every paint calculation value",
		com::clearValues,
		&paintCalculationManager
	);

	CustomLeafOption<PaintDataManager *> calculatePaintAmountOption(
		"calculate amount of paint",
		"Calculates required amount of paint based on other parameters",
		com::calculateResourceAmount,
		&paintCalculationManager
	);

	CustomLeafOption<PaintDataManager *> createPaintPresetOption(
		"create paint calculation preset",
		"Creates a new paint calculation preset based on entered values",
		com::createPreset,
		&paintCalculationManager
	);

	CustomLeafOption<PaintDataManager *> updatePaintPresetOption(
		"update paint calculation preset",
		"Updated data in an existing paint calculation preset",
		com::updatePreset,
		&paintCalculationManager
	);

	CustomLeafOption<PaintDataManager *> removePaintPresetOption(
		"remove paint calculation preset",
		"Removes an existing paint calculation preset",
		com::removePreset,
		&paintCalculationManager
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

	ITableConnection * lacquerConnection = new JSONTableConnection(STRUCTURE_FILE, STANDARD_PRESETS_FILE, "lacquer_calculation");
	LacquerDataManager lacquerCalculationManager(lacquerConnection);

	CustomLeafOption<LacquerDataManager *> writeLacquerParametersOption(
		"write values of parameters",
		"Print current values of all lacquer calculation mode parameters",
		com::writeParameters,
		&lacquerCalculationManager
	);

	CustomLeafOption<LacquerDataManager *> calculateLacquerAmountOption(
		"calculate amount of lacquer",
		"Calculates required amount of lacquer based on entered parameters",
		com::calculateResourceAmount,
		&lacquerCalculationManager
	);

	CustomLeafOption<LacquerDataManager *> loadLacquerCalculationPresetOption(
		"load lacquer calculation preset",
		"Loads values of selected preset into internal storage",
		com::loadPreset,
		&lacquerCalculationManager
	);

	CustomLeafOption<LacquerDataManager *> clearLacquerCalculationValuesOption(
		"remove lacquer calculation data",
		"Clears all entered lacquer calculation parameters",
		com::clearValues,
		&lacquerCalculationManager
	);

	CustomLeafOption<LacquerDataManager *> setLacquerPercentageOption(
		"set lacquer percentage",
		"Sets a percentage value of the lacquer coverage",
		lcom::setPercentage,
		&lacquerCalculationManager
	);

	CustomLeafOption<LacquerDataManager *> setLacquerConsumptionOption(
		"set lacquer consumption",
		"Sets a consumption value of the lacquer",
		lcom::setConsumption,
		&lacquerCalculationManager
	);

	CustomLeafOption<LacquerDataManager *> setLacquerSheetLengthOption(
		"set sheet length",
		"Sets a length value of the sheet",
		lcom::setSheetLength,
		&lacquerCalculationManager
	);

	CustomLeafOption<LacquerDataManager *> setLacquerSheetWidthOption(
		"set sheet width",
		"Sets a width value of the sheet",
		lcom::setSheetWidth,
		&lacquerCalculationManager
	);

	CustomLeafOption<LacquerDataManager *> setLacquerCirculationOption(
		"set circulation",
		"Sets a number of sheets",
		lcom::setCircualtion,
		&lacquerCalculationManager
	);

	CustomLeafOption<LacquerDataManager *> createLacquerPresetOption(
		"create lacquer preset",
		"Creates a new lacquer calculation preset",
		com::createPreset,
		&lacquerCalculationManager
	);

	CustomLeafOption<LacquerDataManager *> updateLacquerPresetOption(
		"update lacquer preset",
		"Updates the selected lacquer calculation preset",
		com::updatePreset,
		&lacquerCalculationManager
	);

	CustomLeafOption<LacquerDataManager *> removeLacquerPresetOption(
		"remove lacquer preset",
		"Removes the selected lacquer calculation preset",
		com::removePreset,
		&lacquerCalculationManager
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

	ITableConnection * foilRollsConnection = new JSONTableConnection(STRUCTURE_FILE, STANDARD_PRESETS_FILE, "foil_rolls");
	FoilRollsDataManager foilRollsDataManager(foilRollsConnection);

	CustomLeafOption<FoilRollsDataManager *> setFoilRollLengthOption(
		"set roll length",
		"Sets the length of the roll",
		from::setLength,
		&foilRollsDataManager
	);

	CustomLeafOption<FoilRollsDataManager *> setFoilRollWidthOption(
		"set roll width",
		"Sets the width of the roll",
		from::setWidth,
		&foilRollsDataManager
	);

	CustomLeafOption<FoilRollsDataManager *> loadFoilRollsPresetOption(
		"load foil roll preset",
		"Loads preset containing data about a roll of foil",
		com::loadPreset,
		&foilRollsDataManager
	);

	CustomLeafOption<FoilRollsDataManager *> createFoilRollsPresetOption(
		"create foil roll preset",
		"Creates a new preset containing data about a roll of foil",
		com::createPreset,
		&foilRollsDataManager
	);

	CustomLeafOption<FoilRollsDataManager *> updateFoilRollsPresetOption(
		"update foil roll preset",
		"Updates the selected foil roll preset with previously entered params",
		com::updatePreset,
		&foilRollsDataManager
	);

	CustomLeafOption<FoilRollsDataManager *> removeFoilRollsPresetOption(
		"remove foil roll preset",
		"Removes the selected foil roll preset",
		com::updatePreset,
		&foilRollsDataManager
	);

	CustomLeafOption<FoilRollsDataManager *> writeFoilRollsManagerParams(
		"write parameters",
		"Writes entered parameters",
		com::writeParameters,
		&foilRollsDataManager
	);

	BaseOptionContainer foilRolls("foil rolls", "Contains methods to manipulate data about foil rolls being used", {
		{'L', &setFoilRollLengthOption},
		{'W', &setFoilRollWidthOption},
		{'l', &loadFoilRollsPresetOption},
		{'w', &writeFoilRollsManagerParams},
		{'+', &createFoilRollsPresetOption},
		{'/', &updateFoilRollsPresetOption},
		{'-', &removeFoilRollsPresetOption}
	});

	ITableConnection * foilConnection = new JSONTableConnection(STRUCTURE_FILE, STANDARD_PRESETS_FILE, "foil_calculation");
	FoilDataManager foilDataManager(foilConnection, &foilRollsDataManager);

	CustomLeafOption<FoilDataManager *> setFoilCirculationOption(
		"set circulation",
		"Sets quantity of the edition",
		fcom::setCirulation,
		&foilDataManager
	);

	CustomLeafOption<FoilDataManager *> setFoilStampLengthOption(
		"set length",
		"Sets length of the stamp",
		fcom::setLength,
		&foilDataManager
	);

	CustomLeafOption<FoilDataManager *> setFoilStampWidthOption(
		"set width",
		"Sets width of the stamp",
		fcom::setWidth,
		&foilDataManager
	);

	CustomLeafOption<FoilDataManager *> setFoilSheetNumberOption(
		"set sheet number",
		"Sets the number of sheets to be printed with one part of the foil",
		fcom::setSheetNumber,
		&foilDataManager
	);

	CustomLeafOption<FoilDataManager *> setFoilLengthReserveOption(
		"set length reserve",
		"Sets reserve value of length of the foil roller",
		fcom::setLengthReserve,
		&foilDataManager
	);

	CustomLeafOption<FoilDataManager *> setFoilWidthReserveOption(
		"set width reserve",
		"Sets reserve value of width of the foil roller",
		fcom::setWidthReserve,
		&foilDataManager
	);

	CustomLeafOption<FoilDataManager *> loadFoilPresetOption(
		"load foil calculation preset",
		"Loads the selected foil calculation preset",
		com::loadPreset,
		&foilDataManager
	);

	CustomLeafOption<FoilDataManager *> writeFoilParametersOption(
		"write parameters",
		"Writes entered foil calculation parameters",
		com::writeParameters,
		&foilDataManager
	);

	CustomLeafOption<FoilDataManager *> calculateFoilLengthOption(
		"calculate foil length",
		"Calculates length of the foil roll",
		fcom::calculateFoilRollLength,
		&foilDataManager
	);

	CustomLeafOption<FoilDataManager *> writeSuitableFoilRollsOption(
		"write suitable rolls",
		"Writes the most suitable rolls of foil in descending order",
		fcom::writeSuitableRolls,
		&foilDataManager
	);

	CustomLeafOption<FoilDataManager *> createFoilPresetOption(
		"create foil preset",
		"Creates the new foil calculation preset",
		com::createPreset,
		&foilDataManager
	);

	CustomLeafOption<FoilDataManager *> updateFoilPresetOption(
		"update foil preset",
		"Updates the selected foil calculation preset",
		com::updatePreset,
		&foilDataManager
	);

	CustomLeafOption<FoilDataManager *> removeFoilPresetOption(
		"remove foil preset",
		"Removes the selected foil calculation preset",
		com::removePreset,
		&foilDataManager
	);

	CustomLeafOption<FoilDataManager *> clearFoilDataOption(
		"clears data",
		"Clears all foil calculation params",
		com::clearValues,
		&foilDataManager
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

	BaseOptionContainer root("root", BASE_HELP_TEXT, {
		{'p', &paintCalculation},
		{'l', &lacquerCalculation},
		{'f', &foilCalculation},
		{'r', &foilRolls}
	}, true);
	root.exec(nullptr, std::cin, std::cout, "\n");

	return 0;
}
