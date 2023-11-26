#include "PaintConsumptionDataManager.hpp"
#include "PresetDoesNotExistException.hpp"
#include "UndefinedValueException.hpp"

PaintConsumptionDataManager::PaintConsumptionDataManager(ITableConnection * conn) {
	setConnection(conn);
	importData(conn->getPresetTemplate());
}

void PaintConsumptionDataManager::importData(std::map<std::string, AutoValue> const &) {}
std::map<std::string, AutoValue> PaintConsumptionDataManager::exportData() const { return {}; }

void PaintConsumptionDataManager::clear() {}

void PaintConsumptionDataManager::setName(std::string const &) {}
void PaintConsumptionDataManager::clearName() {}
std::string PaintConsumptionDataManager::getName() const { return "noname"; }

std::vector<std::string> PaintConsumptionDataManager::getPaintTypes() const { return getConnection()->getPresetNames(); }
std::vector<std::string> PaintConsumptionDataManager::getMaterialTypes() const { return getConnection()->getParamNames(); }

double PaintConsumptionDataManager::getPaintConsumption(std::string const & paintType, std::string const & materialType) const {
	try {
		auto value = getConnection()->getPreset(paintType).at(materialType);
		if (!value.isNull())
			return value;
	} catch (std::out_of_range const &) {
	} catch (PresetDoesNotExistException const &) {}
	throw UndefinedValueException("paint consumption of \"" + paintType + "\" with \"" + materialType + "\"");
}
