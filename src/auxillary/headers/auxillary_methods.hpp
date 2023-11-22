#ifndef AUXILLARY_METHODS_HPP
#define AUXILLARY_METHODS_HPP

#include <stdexcept>
#include <AutoValue.hpp>

#include "UnstableNamedValue.hpp"

namespace auxillary_methods {

	template <typename T>
	void setParam(UnstableNamedValue<T> & param, std::string const & key, std::map<std::string, AutoValue> const & params) {
		param.setName(key);
		try {
			auto value = params.at(key);
			if (!value.isNull())
				param.setValue((T)value);
		} catch (std::out_of_range const &) {}
	}

}

#endif
