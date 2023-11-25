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

	inline std::string getDir(std::string const & url, char divider = '/') {
		if (!url.size())
			return "";

		std::size_t right = url.size();
		for (; right != 0 && url.at(right - 1) != divider; --right);
		return url.substr(0, right);
	}

}

#endif
