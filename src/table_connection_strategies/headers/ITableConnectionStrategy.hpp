#ifndef I_TABLE_CONNECTION_STRATEGY_HPP
#define I_TABLE_CONNECTION_STRATEGY_HPP

#include <map>
#include <vector>
#include <string>

#include <AutoValue.hpp>
#include "TableUpdateList.hpp"

class ITableConnectionStrategy {
public:
	virtual ~ITableConnectionStrategy() {}

	virtual std::vector<AutoValue> getPreset(std::string const & name) const = 0;
	virtual TableUpdateList createPreset(std::string const & name, std::vector<AutoValue> const &) = 0;
	virtual TableUpdateList updatePreset(std::string const & name, std::vector<AutoValue> const &) = 0;
	virtual TableUpdateList removePreset(std::string const & name) = 0;
};

#endif
