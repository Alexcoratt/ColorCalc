#ifndef I_DATA_MANAGER_HPP
#define I_DATA_MANAGER_HPP

#include <map>
#include <vector>
#include <string>
#include <stdexcept>

#include <AutoValue.hpp>

#include "ITableConnection.hpp"

class IDataManager {
public:
	virtual ~IDataManager() {}

	virtual ITableConnection * getConnection() = 0;

	virtual void importData(std::map<std::string, AutoValue> const &) = 0;
	virtual std::map<std::string, AutoValue> exportData() const = 0;

	virtual void clear() = 0;

	virtual void loadPreset(std::string const & name) {
		importData(getConnection()->getPreset(name));
		setName(name);
	};
	virtual void setName(std::string const &) = 0;
	virtual std::string getName() const = 0;

	virtual double calculate() const = 0;
};

#endif
