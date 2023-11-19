#ifndef I_CONNECTION_HPP
#define I_CONNECTION_HPP

#include <cstddef>
#include <vector>
#include <string>
#include <map>

#include "DataContainer.hpp"

// TODO: create ConnectionManager as IConnection's proxy to control saving data into databases
class IConnection {
public:
    virtual ~IConnection() {}

    virtual int getStatus() const = 0;
    virtual bool isReadOnly() const = 0;
    virtual bool hasPreset(std::string const &) const = 0;

    virtual std::vector<std::string> getPresetNames() const = 0;
    virtual std::vector<std::string> getPresetParamNames() const = 0;
    virtual DataContainer getPreset(std::string const &) const = 0;
	virtual DataContainer getPresetTemplate() const = 0;
    virtual void createPreset(DataContainer const &) = 0;
    virtual void updatePreset(DataContainer const &) = 0;
    virtual void removePreset(std::string const &) = 0;
};


#endif
