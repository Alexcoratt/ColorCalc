#ifndef JSON_TABLE_CONNECTION_HPP
#define JSON_TABLE_CONNECTION_HPP

#include <fstream>
#include <map>

#include "ITableConnection.hpp"

class JSONTableConnection : public ITableConnection {
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
	JSONTableConnection(std::string const & structureFileName, std::string const & valuesFileName, std::string const & tableName, bool readOnly = true);
    ~JSONTableConnection();

	int getStatus() const;
    bool isReadOnly() const;

	std::vector<std::string> getPresetNames() const;
    std::vector<std::string> getParamNames() const;
    std::map<std::string, AutoValue> getPreset(std::string const &) const;
    void createPreset(std::string const &, std::map<std::string, AutoValue> const &);
    void updatePreset(std::string const &, std::map<std::string, AutoValue> const &);
    void removePreset(std::string const &);
};

#endif
