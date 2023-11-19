#ifndef I_DATA_CONTAINER_HPP
#define I_DATA_CONTAINER_HPP

#include <map>
#include <string>

#include <AutoValue.hpp>

class IDataContainer {
public:
	virtual ~IDataContainer() {}

	virtual std::map<std::string, AutoValue> exportData() const = 0;
	virtual void importData(std::map<std::string, AutoValue>) = 0;
	virtual void clear() = 0;

	virtual std::string getName() const = 0;
	virtual void setName(std::string const &) = 0;
};

#endif
