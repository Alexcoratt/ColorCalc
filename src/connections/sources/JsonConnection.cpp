#include <cstddef>
#include <string>
#include <iostream>
#include <stdexcept>

#include <NullValue.hpp>

#include "JsonConnection.hpp"

#include <nlohmann/json.hpp>

#include "PresetAlreadyExistsException.hpp"
#include "PresetDoesNotExistException.hpp"

void JsonConnection::download(bool quiet) {
	try {
		if (!quiet)
			std::cout << "Trying to download from " << _valuesFileName << "\t";

		std::ifstream structureFile(_structureFileName);
		_paramNames = nlohmann::json::parse(structureFile).at(_tableName);
		structureFile.close();

		std::ifstream valuesFile(_valuesFileName);
		nlohmann::json presets = nlohmann::json::parse(valuesFile).at(_tableName);
		valuesFile.close();

		for (auto it = presets.begin(); it != presets.end(); ++it) {
			std::vector<AutoValue> values;
			for (nlohmann::basic_json<> const & value : it.value()) {
				if (value.is_number_float())
					values.push_back(value.get<double>());
				else if (value.is_number_unsigned())
					values.push_back(value.get<unsigned long>());
				else if (value.is_number_integer())
					values.push_back(value.get<int>());
				else if (value.is_string())
					values.push_back(value.get<std::string>());
				else
					values.push_back(NullValue());
			}
			_presets[it.key()] = values;
		}

		_status = 0;

		if (!quiet)
			std::cout << "OK\n";
	} catch (nlohmann::json_abi_v3_11_2::detail::parse_error const & err) {
		_status = -1;
		std::cerr << err.what() << std::endl;
	}
}

void JsonConnection::upload(bool quiet) {
	if (!quiet)
		std::cout << "Trying to upload to " << _valuesFileName << "\t";
	if (isReadOnly())
		throw std::runtime_error("connection is read-only");

	std::fstream file(_valuesFileName);
	nlohmann::json data = nlohmann::json::parse(file);
	data[_tableName] = _presets;
	file << data.dump(1) << '\n';
	file.close();

	if (!quiet)
		std::cout << "OK\n";
}

void JsonConnection::syncronize(bool quiet) {
	upload(quiet);
	download(quiet);
}

JsonConnection::JsonConnection(std::string const & structureFileName, std::string const & valueFileName, std::string const & tableName, bool readOnly) : _structureFileName(structureFileName), _valuesFileName(valueFileName), _tableName(tableName) {
	download();
	_readOnly = readOnly;
}

JsonConnection::~JsonConnection() {}
int JsonConnection::getStatus() const { return _status; }
bool JsonConnection::isReadOnly() const { return _readOnly; }
bool JsonConnection::hasPreset(std::string const & name) const { return _presets.find(name) != _presets.end(); }

std::vector<std::string> JsonConnection::getPresetNames() const {
	std::vector<std::string> res;
	for (auto it = _presets.begin(); it != _presets.end(); ++it)
		res.push_back(it->first);
	return res;
}

std::vector<std::string> JsonConnection::getPresetParamNames() const { return _paramNames; }

DataContainer JsonConnection::getPreset(std::string const & name) const {
	if (hasPreset(name))
		throw PresetDoesNotExistException(name);

	DataContainer res(name);
	auto const & values = _presets.at(name);
	auto paramNames = getPresetParamNames();
	unsigned paramCount = paramNames.size();

	for (unsigned i = 0; i < paramCount; ++i)
		res.setValue(paramNames[i], values[i]);

	return res;
}

DataContainer JsonConnection::getPresetTemplate() const {
	DataContainer res("template");
	for (std::string name : getPresetParamNames())
		res.setValue(name, NullValue());
	return res;
}

void JsonConnection::createPreset(DataContainer const & container) {
	auto name = container.getName();
	if (hasPreset(name))
		throw PresetAlreadyExistsException(name);

	std::vector<AutoValue> preset;
	for (auto paramName : getPresetParamNames())
		preset.push_back(container.getValue(paramName));
	_presets[name] = preset;

	std::cout << "Preset named \"" << name << "\" created\n";

	upload();
}

void JsonConnection::updatePreset(DataContainer const & container) {
	auto name = container.getName();
	if (!hasPreset(name))
		throw PresetDoesNotExistException(name);

	std::vector<AutoValue> preset;
	for (auto paramName : getPresetParamNames())
		preset.push_back(container.getValue(paramName));
	_presets[name] = preset;

	std::cout << "Preset named \"" << name << "\" updated\n";

	upload();
}

void JsonConnection::removePreset(std::string const & name) {
	if (!hasPreset(name))
		throw PresetDoesNotExistException(name);

	_presets.erase(name);
	std::cout << "Preset named \"" << name << "\" removed\n";

	upload();
}
