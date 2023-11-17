#ifndef ABSTRACT_DATA_DISPATCHER_HPP
#define ABSTRACT_DATA_DISPATCHER_HPP

#include <map>
#include <vector>
#include <string>
#include <stdexcept>

#include <AutoValue.hpp>

#include "UndefinedValueException.hpp"

class AbstractDataDispatcher {
public:
	virtual ~AbstractDataDispatcher() {}

	virtual std::vector<std::string> getAvailablePresetNames() const = 0;
	virtual std::vector<std::string> getParamNames() const = 0;
	virtual std::map<std::string, std::string> toStringMap() const = 0;

	virtual void clear() = 0;

	virtual std::string getPresetName() const = 0;
	virtual void setPreset(std::string const &) = 0;

	virtual void createPreset(std::string const &) = 0;
	virtual void updatePreset(std::string const &) = 0;
	virtual void removePreset(std::string const &) = 0;

	virtual double calculate() const = 0;
};

namespace common_container_methods {

	inline AutoValue getParam(std::map<std::string, AutoValue> const & params, std::string const key) {
	try {
		AutoValue res = params.at(key);
		if (!res.isNull())
			return res;
	} catch (std::out_of_range const &) {}
	throw UndefinedValueException(key);
}

}

#endif
