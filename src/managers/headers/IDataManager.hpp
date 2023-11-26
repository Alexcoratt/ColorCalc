#ifndef I_DATA_MANAGER_HPP
#define I_DATA_MANAGER_HPP

#include <map>
#include <vector>
#include <string>
#include <stdexcept>

#include <AutoValue.hpp>

#include "ITableConnection.hpp"

class IDataManager {
private:
	ITableConnection * _conn;

public:
	virtual ~IDataManager() {}

	virtual ITableConnection * getConnection() { return _conn; }
	virtual ITableConnection const * getConnection() const { return _conn; }
	virtual void setConnection(ITableConnection * conn) { _conn = conn; }

	virtual void importData(std::map<std::string, AutoValue> const &) = 0;
	virtual std::map<std::string, AutoValue> exportData() const = 0;

	virtual void clear() = 0;

	virtual void setName(std::string const &) = 0;
	virtual void clearName() = 0;
	virtual std::string getName() const = 0;

	virtual double calculate() const = 0;


	virtual void loadPreset(std::string const & name) {
		clear();
		importData(getConnection()->getPreset(name));
		setName(name);
	};

	virtual void createPreset(std::string const & name) {
		getConnection()->createPreset(name, exportData());
		setName(name);
	}

	virtual void updatePreset(std::string const & name) {
		getConnection()->updatePreset(name, exportData());
		setName(name);
	}

	virtual void removePreset(std::string const & name) {
		getConnection()->removePreset(name);
		if (getName() == name)
			clearName();
	}
};

#endif
