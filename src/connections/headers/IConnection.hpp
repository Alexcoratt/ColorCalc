#ifndef I_CONNECTION_HPP
#define I_CONNECTION_HPP

#include <cstddef>
#include <vector>
#include <string>
#include <map>

#include <AutoValue.hpp>

// TODO: create ConnectionManager as IConnection's proxy to control saving data into databases
// FIXME: reduce quantity of repeating methods for different tables
class IConnection {
public:
    virtual ~IConnection() {}

    virtual int getStatus() const = 0;
    virtual bool isReadOnly() const = 0;

    virtual std::vector<std::string> getPresetNames() const = 0;
    virtual std::vector<std::string> getPresetColumns() const = 0;
    virtual std::map<std::string, AutoValue> getPreset(std::string const &) const = 0;
	virtual std::map<std::string, AutoValue> getPresetTemplate() const = 0;
    virtual void createPreset(std::string const &, std::map<std::string, AutoValue> const &) = 0;
    virtual void updatePreset(std::string const &, std::map<std::string, AutoValue> const &) = 0;
    virtual void removePreset(std::string const &) = 0;
};


#endif
