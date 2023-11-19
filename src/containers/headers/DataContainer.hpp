#ifndef DATA_CONTAINER_HPP
#define DATA_CONTAINER_HPP

#include <map>
#include <string>
#include <stdexcept>
#include <set>

#include <AutoValue.hpp>

class DataContainer {
private:
	AutoValue _name;
	std::map<std::string, AutoValue> _data;

public:
	DataContainer(std::string const & = "", std::map<std::string, AutoValue> const & = {});

	std::map<std::string, AutoValue> exportData() const;
	void importData(std::map<std::string, AutoValue> const &);
	std::set<std::string> getKeys() const;
	void clear();

	AutoValue const & name() const;
	AutoValue & name();

	AutoValue const & at(std::string const &) const;
	AutoValue & at(std::string const &);

	AutoValue & operator[](std::string const &);

	// map iteration
	std::map<std::string, AutoValue>::iterator begin();
	std::map<std::string, AutoValue>::const_iterator begin() const;

	std::map<std::string, AutoValue>::iterator end();
	std::map<std::string, AutoValue>::const_iterator end() const;
};

#endif
