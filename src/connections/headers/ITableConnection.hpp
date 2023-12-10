#ifndef I_TABLE_CONNECTION_HPP
#define I_TABLE_CONNECTION_HPP

#include <algorithm>
#include <cstddef>
#include <vector>
#include <string>
#include <map>

#include <AutoValue.hpp>

class ITableConnection {
public:
    virtual ~ITableConnection() {}

    virtual int getStatus() const = 0;
    virtual bool isReadOnly() const = 0;

    virtual std::string getName() const = 0;

    virtual std::vector<std::string> getParamNames() const = 0;
    virtual std::vector<std::string> getPresetNames() const = 0;

    virtual bool hasPreset(std::string const & name) const;

    virtual std::map<std::string, AutoValue> getPreset(std::string const &) const = 0;
	virtual std::map<std::string, AutoValue> getPresetTemplate() const;

    virtual void createPreset(std::string const &, std::map<std::string, AutoValue> const &) = 0;
    virtual void updatePreset(std::string const &, std::map<std::string, AutoValue> const &) = 0;
    virtual void removePreset(std::string const &) = 0;
};


inline bool ITableConnection::hasPreset(std::string const & name) const {
    auto names = getPresetNames();
    return std::find(names.begin(), names.end(), name) != names.end();
}

inline std::map<std::string, AutoValue> ITableConnection::getPresetTemplate() const {
    std::map<std::string, AutoValue> res;
    for (std::string name : getParamNames())
        res[name];
    return res;
};


#endif
