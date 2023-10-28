#ifndef COMMON_METHODS_HPP
#define COMMON_METHODS_HPP

#include <cstddef>
#include <vector>
#include "nlohmann/json.hpp"

namespace common_methods {

	template <typename T>
	std::size_t getIndex(std::vector<T> const &, T const &);

	bool isNull(nlohmann::json const &);

}

#endif
