#include "JsonConnection.hpp"
#include "json.hpp"
#include "common_methods.hpp"
#include <cstddef>
#include <string>

#define TABLES "tables"

#define PAINT_CONSUMPTION_TABLE "расход краски"
#define PAINT_TYPES "rows"
#define MATERIAL_TYPES "columns"
#define TYPES_VALUES "values"

#define PAINT_CALCULATION_TABLE "расчет печатной краски"
#define PAINT_COLUMNS "columns"
#define PAINT_PRESETS "rows"
#define PAINT_TYPE_COLUMN "тип краски"
#define MATERIAL_TYPE_COLUMN "тип материала"

//using json_type_error = nlohmann::json_abi_v3_11_2::detail::type_error;
namespace cm = common_methods;

nlohmann::json JsonConnection::getTable(std::string const & name) const {
	return _data[TABLES][name];
}

JsonConnection::JsonConnection(nlohmann::json const & data) : _data(data) {}
JsonConnection::JsonConnection(std::ifstream & stream) : _data(nlohmann::json::parse(stream)) {}

std::vector<std::string> JsonConnection::getPaintTypes() const { return getTable(PAINT_CONSUMPTION_TABLE)[PAINT_TYPES]; }
std::vector<std::string> JsonConnection::getMaterialTypes() const { return getTable(PAINT_CONSUMPTION_TABLE)[MATERIAL_TYPES]; }

double JsonConnection::getPaintConsumption(std::string const & paintType, std::string const & materialType) const {
	std::size_t paintIndex = cm::getIndex(getPaintTypes(), paintType);
	std::size_t materialIndex = cm::getIndex(getPaintTypes(), materialType);
	return getTable(PAINT_CONSUMPTION_TABLE)[TYPES_VALUES][paintIndex][materialIndex];
}

std::vector<std::string> JsonConnection::getPaintPresetsNames() const {
	std::vector<std::string> res;
	nlohmann::json data = getTable(PAINT_CALCULATION_TABLE)[PAINT_PRESETS];
	for (auto iter = data.begin(); iter != data.end(); ++iter)
		res.push_back(iter.key());
	return res;
}

std::vector<std::string> JsonConnection::getPaintColumns() const { return getTable(PAINT_CALCULATION_TABLE)[PAINT_COLUMNS]; }

nlohmann::json JsonConnection::getPaintPreset(std::string const & name) const {
	nlohmann::json valueArrays = getTable(PAINT_CALCULATION_TABLE)[PAINT_PRESETS][name];
	std::vector<std::string> columns = getPaintColumns();
	nlohmann::json res;

	std::size_t count = 0;
	for (nlohmann::json valueArray : valueArrays)
		res[columns[count++]] = valueArray;

	res[PAINT_TYPE_COLUMN] = getPaintTypes()[res[PAINT_TYPE_COLUMN]];
	res[MATERIAL_TYPE_COLUMN] = getMaterialTypes()[res[MATERIAL_TYPE_COLUMN]];

	return res;
}

nlohmann::json JsonConnection::getPaintPresetTemplate() const {
	nlohmann::json res;
	for (std::string const & column : getPaintColumns())
		res[column] = nlohmann::json::value_t::null;
	return res;
}
