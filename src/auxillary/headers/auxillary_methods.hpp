#ifndef AUXILLARY_METHODS_HPP
#define AUXILLARY_METHODS_HPP

#include <fstream>

#include <stdexcept>
#include <AutoValue.hpp>

#include "UnstableNamedValue.hpp"

namespace auxillary_methods {

	template <typename T>
	void setParam(UnstableNamedValue<T> & param, std::map<std::string, AutoValue> const & params, std::string const & key) {
		param.setName(key);
		try {
			auto value = params.at(key);
			if (!value.isNull())
				param.setValue((T)value);
		} catch (std::out_of_range const &) {}
	}

	template <typename T>
	void setMapValue(std::map<std::string, AutoValue> & map, UnstableNamedValue<T> const & param) {
		try {
			map[param.getName()] = param.getValue();
		} catch (UndefinedValueException const &) {
			map[param.getName()] = AutoValue();
		}
	}

	inline std::map<std::string, std::string> readBaseConf(std::string const & filename) {
		std::map<std::string, std::string> res;
		std::ifstream file(filename);

		if (file.fail()) {
			file.close();
			throw std::runtime_error("Critical error: Base config file is not found");
		}

		while(!file.eof()) {
			std::string key;
			std::string value;
			std::getline(file, key, '=');
			std::getline(file, value);
			res[key] = value;
		}
		file.close();
		return res;
	}

}

#endif
