#include "DataContainer.hpp"

DataContainer::DataContainer(std::string const & name, std::map<std::string, AutoValue> const & data) : _name(name), _data(data) {}

std::map<std::string, AutoValue> DataContainer::exportData() const { return _data; }
void DataContainer::importData(std::map<std::string, AutoValue> const & data) { _data = data; }

std::set<std::string> DataContainer::getKeys() const {
	std::set<std::string> res;
	for (auto it = _data.begin(); it != _data.end(); ++it)
		res.insert(it->first);
	return res;
}

void DataContainer::clear() {
	_name.clear();
	_data.clear();
}

AutoValue const & DataContainer::name() const { return _name; }
AutoValue & DataContainer::name() { return _name; }

AutoValue const & DataContainer::at(std::string const & key) const {
	return _data.at(key);
}

AutoValue & DataContainer::at(std::string const & key) {
	return _data.at(key);
}

AutoValue & DataContainer::operator[](std::string const & key) { return _data[key]; }

std::map<std::string, AutoValue>::iterator DataContainer::begin() { return _data.begin(); }
std::map<std::string, AutoValue>::const_iterator DataContainer::begin() const { return _data.begin(); }

std::map<std::string, AutoValue>::iterator DataContainer::end() { return _data.end(); }
std::map<std::string, AutoValue>::const_iterator DataContainer::end() const { return _data.end(); }
