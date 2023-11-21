#ifndef TABLE_UPDATE_LIST_HPP
#define TABLE_UPDATE_LIST_HPP

#include <map>
#include <string>
#include <vector>

#include <AutoValue.hpp>

struct TableUpdateList {
	std::map<std::string, std::vector<AutoValue>> toCreate;
	std::map<std::string, std::vector<AutoValue>> toUpdate;
	std::vector<std::string> toDelete;
};

#endif
