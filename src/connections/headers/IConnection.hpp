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

    // FIXME: please do that as it supposed to be after you succeed
    // All inter-dispatcher methods must be out of connection
    // Queries for paint/material types table
    virtual std::vector<std::string> getPaintTypes() const = 0;
    virtual std::vector<std::string> getMaterialTypes() const = 0;
    virtual double getPaintConsumption(std::string const &, std::string const &) const = 0;

    // Queires for paint presets
    virtual std::vector<std::string> getPaintPresetNames() const = 0;
    virtual std::vector<std::string> getPaintPresetColumns() const = 0;
    virtual std::map<std::string, AutoValue> getPaintPreset(std::string const &) const = 0;
	virtual std::map<std::string, AutoValue> getPaintPresetTemplate() const = 0;
    virtual void createPaintPreset(std::string const &, std::map<std::string, AutoValue> const &) = 0;
    virtual void updatePaintPreset(std::string const &, std::map<std::string, AutoValue> const &) = 0;
    virtual void removePaintPreset(std::string const &) = 0;

    // Queries for lacquer presets
    virtual std::vector<std::string> getLacquerPresetNames() const = 0;
    virtual std::vector<std::string> getLacquerPresetColumns() const = 0;
    virtual std::map<std::string, AutoValue> getLacquerPreset(std::string const &) const = 0;
	virtual std::map<std::string, AutoValue> getLacquerPresetTemplate() const = 0;
    virtual void createLacquerPreset(std::string const &, std::map<std::string, AutoValue> const &) = 0;
    virtual void updateLacquerPreset(std::string const &, std::map<std::string, AutoValue> const &) = 0;
    virtual void removeLacquerPreset(std::string const &) = 0;

    // Queries for foil presets
    virtual std::vector<std::string> getFoilPresetNames() const = 0;
    virtual std::vector<std::string> getFoilPresetColumns() const = 0;
    virtual std::map<std::string, AutoValue> getFoilPreset(std::string const &) const = 0;
    virtual std::map<std::string, AutoValue> getFoilPresetTemplate() const = 0;
    virtual void createFoilPreset(std::string const &, std::map<std::string, AutoValue> const &) = 0;
    virtual void updateFoilPreset(std::string const &, std::map<std::string, AutoValue> const &) = 0;
    virtual void removeFoilPreset(std::string const &) = 0;

    // Queries for foil roll presets
    virtual std::vector<std::string> getFoilRollPresetNames() const = 0;
    virtual std::vector<std::string> getFoilRollPresetColumns() const = 0;
    virtual std::map<std::string, AutoValue> getFoilRollPreset(std::string const &) const = 0;
    virtual std::map<std::string, AutoValue> getFoilRollPresetTemplate() const = 0;
    virtual void createFoilRollPreset(std::string const &, std::map<std::string, AutoValue> const &) = 0;
    virtual void updateFoilRollPreset(std::string const &, std::map<std::string, AutoValue> const &) = 0;
    virtual void removeFoilRollPreset(std::string const &) = 0;

    // WARNING: inter-dispatcher method
    virtual std::vector<std::string> selectFoilRollPresets(double minLength, double minWidth) const;
};


#endif
