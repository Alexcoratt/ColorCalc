#ifndef I_TABLE_CONNECTION_HPP
#define I_TABLE_CONNECTION_HPP

#include <cstddef>
#include <vector>
#include <string>
#include <map>

#include <AutoValue.hpp>

// TODO: create ConnectionManager as IConnection's proxy to control saving data into databases
class ITableConnection {
public:
    virtual ~ITableConnection() {}

    virtual int getStatus() const = 0;
    virtual bool isReadOnly() const = 0;
    virtual bool hasPreset(std::string const &) const = 0;

    virtual std::vector<std::string> getParamNames() const = 0;
    virtual std::vector<std::string> getPresetNames() const = 0;

    virtual bool hasPreset(std::string const & name) {
        auto names = getPresetNames();
        return std::find(names.begin(), names.end(), name) != names.end();
    }

    virtual std::map<std::string, AutoValue> getPreset(std::string const &) const = 0;
	virtual std::map<std::string, AutoValue> getPresetTemplate() const = 0;
    virtual void createPreset(std::string const &, std::map<std::string, AutoValue> const &) = 0;
    virtual void updatePreset(std::string const &, std::map<std::string, AutoValue> const &) = 0;
    virtual void removePreset(std::string const &) = 0;
};


#endif
