#ifndef JSON_CONNECTION_HPP
#define JSON_CONNECTION_HPP

#include <fstream>
#include <map>

#include "IConnection.hpp"

class JsonConnection : public IConnection {
private:
	std::string _structureFileName;
	std::string _valuesFileName;

    std::string _tableName;
	std::vector<std::string> _paramNames;
    std::map<std::string, std::vector<AutoValue>> _presets;

	int _status;
    bool _readOnly;

	void download(bool quiet = false);
	void upload(bool quiet = false);
	void syncronize(bool quiet = false);

public:
	JsonConnection(std::string const & structureFileName, std::string const & valuesFileName, std::string const & tableName, bool readOnly = true);
    ~JsonConnection();

	int getStatus() const;
    bool isReadOnly() const;
    bool hasPreset(std::string const &) const;

	std::vector<std::string> getPresetNames() const;
    std::vector<std::string> getPresetParamNames() const;
    DataContainer getPreset(std::string const &) const;
	DataContainer getPresetTemplate() const;
    void createPreset(DataContainer const &);
    void updatePreset(DataContainer const &);
    void removePreset(std::string const &);
};

#endif
