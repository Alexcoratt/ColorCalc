#include <cstddef>
#include <string>
#include <iostream>
#include <stdexcept>

#include <NullValue.hpp>

#include "JSONTableConnection.hpp"

#include <nlohmann/json.hpp>

#include "PresetAlreadyExistsException.hpp"
#include "PresetDoesNotExistException.hpp"

void JSONTableConnection::download() {
	try {
		if (!_quiet)
			std::cout << "Trying to download from " << _valuesFileName << ':' << _tableName << '\t';

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

		if (!_quiet)
			std::cout << "OK\n";
	} catch (nlohmann::json_abi_v3_11_2::detail::parse_error const & err) {
		_status = -1;
		std::cerr << err.what() << std::endl;
	}
}

void JSONTableConnection::upload() {
	if (!_quiet)
		std::cout << "Trying to upload to " << _valuesFileName << ':' << _tableName << '\t';
	if (isReadOnly())
		throw std::runtime_error("connection is read-only");

	std::ifstream ifile(_valuesFileName);
	nlohmann::json data = nlohmann::json::parse(ifile);
	ifile.close();

	data[_tableName] = nlohmann::basic_json<>();
	for (auto it = _presets.begin(); it != _presets.end(); ++it) {
		std::string presetName {it->first};
		nlohmann::json preset;
		for (auto value : it->second) {
			if (value.isDouble())
				preset.push_back((double)value);
			else if (value.isUnsignedLongInt())
				preset.push_back((unsigned long)value);
			else if (value.isInt())
				preset.push_back((int)value);
			else if (value.isString())
				preset.push_back((std::string)value);
			else
				preset.push_back(nlohmann::json::value_t::null);
		}
		data[_tableName][presetName] = preset;
	}

	std::ofstream ofile(_valuesFileName);
	ofile << data.dump(1) << '\n';
	ofile.close();

	if (!_quiet)
		std::cout << "OK\n";
}

void JSONTableConnection::syncronize() {
	upload();
	download();
}

JSONTableConnection::JSONTableConnection(std::string const & structureFileName, std::string const & valueFileName, std::string const & tableName, bool readOnly, bool quiet) : _structureFileName(structureFileName), _valuesFileName(valueFileName), _tableName(tableName) {
	_readOnly = readOnly;
	_quiet = quiet;
	download();
}

JSONTableConnection::~JSONTableConnection() {}
int JSONTableConnection::getStatus() const { return _status; }
bool JSONTableConnection::isReadOnly() const { return _readOnly; }

std::vector<std::string> JSONTableConnection::getPresetNames() const {
	std::vector<std::string> res;
	for (auto it = _presets.begin(); it != _presets.end(); ++it)
		res.push_back(it->first);
	return res;
}

std::vector<std::string> JSONTableConnection::getParamNames() const { return _paramNames; }

std::map<std::string, AutoValue> JSONTableConnection::getPreset(std::string const & name) const {
	if (!hasPreset(name))
		throw PresetDoesNotExistException(name);

	std::map<std::string, AutoValue> res;
	auto const & values = _presets.at(name);
	auto paramNames = getParamNames();
	unsigned paramCount = paramNames.size();

	for (unsigned i = 0; i < paramCount; ++i)
		res[paramNames[i]] = values[i];

	return res;
}

void JSONTableConnection::createPreset(std::string const & name, std::map<std::string, AutoValue> const & params) {
	if (hasPreset(name))
		throw PresetAlreadyExistsException(name);

	std::vector<AutoValue> preset;
	for (auto paramName : getParamNames())
		preset.push_back(params.at(paramName));
	_presets[name] = preset;

	std::cout << "Preset named \"" << name << "\" created\n";

	upload();
}

void JSONTableConnection::updatePreset(std::string const & name, std::map<std::string, AutoValue> const & params) {
	if (!hasPreset(name))
		throw PresetDoesNotExistException(name);

	std::vector<AutoValue> preset;
	for (auto paramName : getParamNames())
		preset.push_back(params.at(paramName));
	_presets[name] = preset;

	std::cout << "Preset named \"" << name << "\" updated\n";

	upload();
}

void JSONTableConnection::removePreset(std::string const & name) {
	if (!hasPreset(name))
		throw PresetDoesNotExistException(name);

	_presets.erase(name);
	std::cout << "Preset named \"" << name << "\" removed\n";

	upload();
}
