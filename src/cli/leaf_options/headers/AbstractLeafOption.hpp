#ifndef ABSTRACT_LEAF_OPTION_HPP
#define ABSTRACT_LEAF_OPTION_HPP

#include "IOption.hpp"

class AbstractLeafOption : public IOption {
public:
	virtual std::map<char, IOption *> getCommands() const { return {}; }
};

#endif
