#ifndef COMMON_METHODS_HPP
#define COMMON_METHODS_HPP

#include <cstddef>
#include <vector>
#include <nlohmann/json.hpp>

namespace common_methods {

	template <typename T>
	inline std::size_t getIndex(std::vector<T> const & vect, T search) {
		std::size_t count = 0;
		for (T value : vect) {
			if (value == search)
				return count;
			++count;
		}
		throw std::invalid_argument("getIndex: required value is not found");
	}

	template <typename T>
	inline std::size_t isIn(std::vector<T> const & vect, T search) {
		for (T value : vect)
			if (value == search)
				return true;
		return false;
	}

	bool jsonIsNull(nlohmann::json const & value);

}

#endif
