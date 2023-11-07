#include "HelpOption.hpp"
#include "BaseOptionContainer.hpp"
#include <cstdlib>
#include <stdexcept>
#include <vector>

template <typename T>
void qsort(std::vector<T> & vect) {
	std::qsort
    (
        vect.data(),
        vect.size(),
        sizeof(T),
        [](const void* x, const void* y)
        {
            T const arg1 = *static_cast<T const *>(x);
            T const arg2 = *static_cast<T const *>(y);
            const auto cmp = arg1 > arg2;
            if (cmp < 0)
                return -1;
            if (cmp > 0)
                return 1;
            return 0;
        }
    );
}

struct Keys {
	std::vector<char> baseKeys;
	std::vector<char> otherKeys;
};

Keys distributeKeys(std::map<char, IOption *> m) {
	Keys res;
	for (auto pair : m) {
		if (pair.second->getIsBaseOption())
			res.baseKeys.push_back(pair.first);
		else
			res.otherKeys.push_back(pair.first);
	}

	qsort(res.baseKeys);
	qsort(res.otherKeys);
	return res;
}

void HelpOption::exec(IOption * parent, std::istream &, std::ostream & output, std::string const & endline) {
	BaseOptionContainer * parentContainer = dynamic_cast<BaseOptionContainer *>(parent);

	if (parentContainer) {
		Keys keys = distributeKeys(parentContainer->getOptions());

		output << "Available options:" << endline;
		for (auto key : keys.otherKeys) {
			output << key << "\t" << parentContainer->getOption(key)->getName();
			if (parentContainer->getOption(key)->getHelp().size() > 0)
				output << ": " << parentContainer->getOption(key)->getHelp();
			output << endline;
		}

		output << endline;
		for (auto key : keys.baseKeys) {
			output << key << "\t" << parentContainer->getOption(key)->getName();
			if (parentContainer->getOption(key)->getHelp().size() > 0)
				output << ": " << parentContainer->getOption(key)->getHelp();
			output << endline;
		}
	} else {
		throw new std::invalid_argument("Parent must be pointer to a container");
	}
}
