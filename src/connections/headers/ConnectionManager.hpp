#ifndef CONNECTION_MANAGER_HPP
#define CONNECTION_MANAGER_HPP

#include "IConnection.hpp"

class ConnectionManager : public IConnection {
private:
	std::vector<IConnection *> _connections;

public:
	ConnectionManager(std::vector<IConnection *> const & connections);

	int getStatus() const;
	bool isReadOnly() const;

	std::vector<std::string> getPaintTypes() const;
    std::vector<std::string> getMaterialTypes() const;
    double getPaintConsumption(std::string const & paintType, std::string const & materialType) const;

    std::vector<std::string> getPaintPresetNames() const;
    std::vector<std::string> getPaintPresetColumns() const;
    std::map<std::string, AutoValue> getPaintPreset(std::string const &) const;
	std::map<std::string, AutoValue> getPaintPresetTemplate() const;
    void createPaintPreset(std::string const &, std::map<std::string, AutoValue> const &);
    void updatePaintPreset(std::string const &, std::map<std::string, AutoValue> const &);
    void removePaintPreset(std::string const &);

    std::vector<std::string> getLacquerPresetNames() const;
    std::vector<std::string> getLacquerPresetColumns() const;
    std::map<std::string, AutoValue> getLacquerPreset(std::string const &) const;
	std::map<std::string, AutoValue> getLacquerPresetTemplate() const;
    void createLacquerPreset(std::string const &, std::map<std::string, AutoValue> const &);
    void updateLacquerPreset(std::string const &, std::map<std::string, AutoValue> const &);
    void removeLacquerPreset(std::string const &);

    std::vector<std::string> getFoilPresetNames() const;
    std::vector<std::string> getFoilPresetColumns() const;
    std::map<std::string, AutoValue> getFoilPreset(std::string const &) const;
    std::map<std::string, AutoValue> getFoilPresetTemplate() const;
    void createFoilPreset(std::string const &, std::map<std::string, AutoValue> const &);
    void updateFoilPreset(std::string const &, std::map<std::string, AutoValue> const &);
    virtual void removeFoilPreset(std::string const &);

    std::vector<std::string> getFoilRollPresetNames() const;
    std::vector<std::string> getFoilRollPresetColumns() const;
    std::map<std::string, AutoValue> getFoilRollPreset(std::string const &) const;
    std::map<std::string, AutoValue> getFoilRollPresetTemplate() const;
    void createFoilRollPreset(std::string const &, std::map<std::string, AutoValue> const &);
    void updateFoilRollPreset(std::string const &, std::map<std::string, AutoValue> const &);
    void removeFoilRollPreset(std::string const &);

    std::vector<std::string> selectFoilRollPresets(double, double) const;

};

#endif
