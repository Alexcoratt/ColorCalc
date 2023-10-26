#ifndef OPTION_METHODS_HPP
#define OPTION_METHODS_HPP

#include <functional>
#include <vector>
#include <string>
#include <algorithm>

#include "nlohmann/json.hpp"
#include "nlohmann/json_fwd.hpp"

#include "PaintDataContainer.hpp"

namespace option_methods {

	inline std::vector<std::string> getKeys(nlohmann::json const & map) {
		std::vector<std::string> keys;
		for (auto it = map.begin(); it != map.end(); ++it)
			keys.push_back(it.key());

		std::sort(keys.begin(), keys.end());
		return keys;
	}

	inline void printData();


}

#endif
