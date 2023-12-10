#include <cstddef>
#include <string>
#include <iostream>
#include <stdexcept>

#include <NullValue.hpp>
#include <UnsignedLongIntValue.hpp>

#include "JSONTableConnection.hpp"

#include <json/json.h>

#include "PresetAlreadyExistsException.hpp"
#include "PresetDoesNotExistException.hpp"

void JSONTableConnection::download() {
	try {
		if (!_quiet)
			std::cout << "Trying to download from " << _valuesFileName << ':' << _tableName << '\t';

		std::ifstream structureFile(_structureFileName);
		Json::Value structureJson;
		structureFile >> structureJson;
		structureFile.close();

		auto structureTable = structureJson[_tableName];
		for (auto iter = structureTable.begin(); iter != structureTable.end(); ++iter)
			_paramNames.push_back(iter->asString());

		std::ifstream valuesFile(_valuesFileName);
		Json::Value valuesJson;
		valuesFile >> valuesJson;
		valuesFile.close();

		auto valuesTable = valuesJson[_tableName];
		//nlohmann::json presets = nlohmann::json::parse(valuesFile).at(_tableName);

		for (auto it = valuesTable.begin(); it != valuesTable.end(); ++it) {
			std::vector<AutoValue> values;
			for (auto presetIter = it->begin(); presetIter != it->end(); ++presetIter) {
				if (presetIter->isDouble())
					values.push_back(presetIter->asDouble());
				else if (presetIter->isUInt())
					values.push_back(UnsignedLongIntValue(presetIter->asUInt()));
				else if (presetIter->isInt())
					values.push_back(presetIter->asInt());
				else if (presetIter->isString())
					values.push_back(presetIter->asString());
				else
					values.push_back(NullValue());
			}
			_presets[it.key().asString()] = values;
		}

		_status = 0;

		if (!_quiet)
			std::cout << "OK\n";
	} catch (std::exception const & err) {
		_status = -1;
		std::cerr << err.what() << std::endl;
	}
}

void JSONTableConnection::upload() {
	if (!_quiet)
		std::cout << "Trying to upload to " << _valuesFileName << ':' << _tableName << '\t';
	if (isReadOnly())
		throw std::runtime_error("connection is read-only");

	std::ifstream presetFile(_valuesFileName);
	Json::Value data;
	presetFile >> data;
	presetFile.close();
	//nlohmann::json data = nlohmann::json::parse(ifile);

	data[_tableName] = Json::Value{};
	for (auto it = _presets.begin(); it != _presets.end(); ++it) {
		std::string presetName {it->first};
		Json::Value preset;
		for (auto value : it->second) {
			if (value.isDouble())
				preset.append((double)value);
			else if (value.isUnsignedLongInt())
				preset.append(Json::UInt((unsigned long)value));
			else if (value.isInt())
				preset.append((int)value);
			else if (value.isString())
				preset.append((std::string)value);
			else
				preset.append(Json::nullValue);
		}
		data[_tableName][presetName] = preset;
	}

	std::ofstream ofile(_valuesFileName);
	ofile << data << '\n';
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

std::string JSONTableConnection::getName() const { return _valuesFileName + ":" + _tableName; }

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
