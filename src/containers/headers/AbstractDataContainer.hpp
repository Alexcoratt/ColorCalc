#ifndef ABSTRACT_DATA_CONTAINER_HPP
#define ABSTRACT_DATA_CONTAINER_HPP

#include <map>
#include <vector>
#include <string>

class AbstractDataContainer {
public:
	virtual ~AbstractDataContainer() {}

	virtual std::vector<std::string> getParamNames() const = 0;
	virtual std::map<std::string, std::string> toStringMap() const = 0;

	virtual void clear() = 0;

	virtual std::string getPresetName() const = 0;
	virtual void setPreset(std::string const &) = 0;

	virtual double calculate() const = 0;
};

#endif
