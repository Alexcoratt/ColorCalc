#include "common_methods.hpp"

template <typename T>
std::size_t common_methods::getIndex(std::vector<T> const & vect, T const & search) {
	for (T value : vect)
		if (value == search)
			return true;
	return false;
}

bool common_methods::isNull(nlohmann::json const & value) { return value == nlohmann::json::value_t::null; }
