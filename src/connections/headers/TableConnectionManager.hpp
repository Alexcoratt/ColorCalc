#ifndef TABLE_CONNECTION_MANAGER_HPP
#define TABLE_CONNECTION_MANAGER_HPP

#include "ITableConnection.hpp"

class TableConnectionManager : public ITableConnection {
private:
	std::vector<ITableConnection *> _connections;

public:
	TableConnectionManager(std::vector<ITableConnection *> const &);

	std::vector<ITableConnection *> getConnections();
	std::vector<ITableConnection const *> getConnections() const;

	int getStatus() const;
	bool isReadOnly() const;

	std::string getName() const;

	std::vector<std::string> getParamNames() const;
	std::vector<std::string> getPresetNames() const;

	std::map<std::string, AutoValue> getPreset(std::string const &) const;

	void createPreset(std::string const &, std::map<std::string, AutoValue> const &);
    void updatePreset(std::string const &, std::map<std::string, AutoValue> const &);
    void removePreset(std::string const &);
};

#endif
