#ifndef ABSTRACT_DATA_DISPATCHER_HPP
#define ABSTRACT_DATA_DISPATCHER_HPP

#include <map>
#include <vector>
#include <string>
#include <stdexcept>

#include <AutoValue.hpp>

#include "IConnection.hpp"
#include "UndefinedValueException.hpp"

class AbstractDataDispatcher {
protected:
	IConnection * _conn;
	DataContainer _data;

public:
	virtual ~AbstractDataDispatcher() {}

	virtual IConnection * getConnection();

	virtual std::vector<std::string> getAvailablePresetNames() const;
	virtual std::vector<std::string> getParamNames() const;
	virtual std::map<std::string, std::string> toStringMap() const;

	virtual void clear();

	virtual std::string getPresetName() const;
	virtual void setPreset(std::string const &);

	virtual void createPreset(std::string const &);
	virtual void updatePreset(std::string const &);
	virtual void removePreset(std::string const &);

	virtual double calculate() const = 0;
};

namespace common_dispatcher_methods {

	template <typename T>
	T getValue(DataContainer const & data, std::string const & key) {
		try {
			auto value = data.at(key);
			if (!value.isNull())
				return (T)value;
		} catch (std::out_of_range const &) {}
		throw UndefinedValueException(key);
	}

}

#endif
