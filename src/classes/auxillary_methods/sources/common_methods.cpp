#include <stdexcept>
#include "common_methods.hpp"

bool common_methods::jsonIsNull(nlohmann::json const & value) { return value == nlohmann::json::value_t::null; }
