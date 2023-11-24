#ifndef AUXILLARY_METHODS_HPP
#define AUXILLARY_METHODS_HPP

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
}

#endif
