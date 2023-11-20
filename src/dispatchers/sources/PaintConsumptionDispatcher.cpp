#include <format>
#include "PaintConsumptionDispatcher.hpp"
#include "PresetDoesNotExistException.hpp"

PaintConsumptionDispatcher::PaintConsumptionDispatcher(IConnection * conn) {
	_conn = conn;
	_data = conn->getPresetTemplate();
}

std::vector<std::string> PaintConsumptionDispatcher::getPaintTypes() const { return getAvailablePresetNames(); }
std::vector<std::string> PaintConsumptionDispatcher::getMaterialTypes() const { return getParamNames(); }

double PaintConsumptionDispatcher::getPaintConsumption(std::string const & paintType, std::string const & materialType) const {
	try {
		auto preset = _conn->getPreset(paintType);
		return common_dispatcher_methods::getValue<double>(preset, materialType);
	} catch (UndefinedValueException const &) {
	} catch (PresetDoesNotExistException const &) {}
	throw UndefinedValueException("paint consumption of \"" + paintType + "\" with \"" + materialType + "\"");
}
