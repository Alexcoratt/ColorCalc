#ifndef ABSTRACT_DATA_CONTAINER_HPP
#define ABSTRACT_DATA_CONTAINER_HPP

#include <string>
#include "IConnection.hpp"
#include "common_methods.hpp"

#include "UndefinedValueException.hpp"

class AbstractDataContainer {
protected:
	IConnection * _conn;
	std::string _presetName;
	nlohmann::json _data;

	template <typename T>
	T getValue(std::string const & key) const {
		if (common_methods::jsonIsNull(_data[key]))
			throw UndefinedValueException(key);
		return _data[key];
	}

	template <typename T>
	inline void setValue(std::string const & key, T value) {
		_presetName.clear();
		_data[key] = value;
	}

	inline void clear(std::string const & key) { _data[key] = nlohmann::json::value_t::null; }

public:
	virtual ~AbstractDataContainer() {}

	inline virtual IConnection * getConnection() const { return _conn; }
	virtual std::vector<std::string> getColumns() const = 0;
	virtual nlohmann::json exportData() const = 0;

	virtual void clearData() = 0;

	inline virtual std::string getPresetName() const {
		if (_presetName.size() > 0)
			return _presetName;
		throw UndefinedValueException("preset name");
	}
	virtual std::vector<std::string> getAvailablePresetsNames() const = 0;
	virtual void setPreset(std::string const &) = 0;

	virtual double calculate() const = 0;
};

#endif
