#ifndef DATA_CONTAINER_HPP
#define DATA_CONTAINER_HPP

#include <map>
#include <string>
#include <stdexcept>

#include <AutoValue.hpp>

#include "UndefinedValueException.hpp"

class DataContainer {
private:
	std::string _name;
	std::map<std::string, AutoValue> _data;

public:
	DataContainer(std::string const & name, std::map<std::string, AutoValue> const & data = {}) : _name(name), _data(data) {}

	std::map<std::string, AutoValue> exportData() const { return _data; }
	void importData(std::map<std::string, AutoValue> const & data) { _data = data; }
	void clear() { _data.clear(); }

	std::string getName() const { return _name; }
	void setName(std::string const & name) { _name = name; }

	AutoValue getValue(std::string const & key) const {
		try {
			AutoValue const & res = _data.at(key);
			if (!res.isNull())
				return res;
		} catch (std::out_of_range const &) {}
		throw UndefinedValueException(key);
	}
	void setValue(std::string const & key, AutoValue const & value) { _data[key] = value; }
};

#endif
