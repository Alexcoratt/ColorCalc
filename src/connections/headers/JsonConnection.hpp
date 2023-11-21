#ifndef JSON_CONNECTION_HPP
#define JSON_CONNECTION_HPP

#include <fstream>
#include <map>

#include "ITableConnection.hpp"

class JsonConnection : public ITableConnection {
private:
	std::string _structureFileName;
	std::string _valuesFileName;

    std::string _tableName;
	std::vector<std::string> _paramNames;
	ITableConnectionStrategy * _strategy;

	int _status;
    bool _readOnly;

	void download(bool quiet = false);
	void upload(bool quiet = false);
	void syncronize(bool quiet = false);

public:
	JsonConnection(std::string const & structureFileName, std::string const & valuesFileName, std::string const & tableName, bool readOnly = true, ITableConnectionStrategy * strategy = nullptr);
    ~JsonConnection();

	int getStatus() const;
    bool isReadOnly() const;
    bool hasPreset(std::string const &) const;

	std::vector<std::string> getPresetNames() const;
    std::vector<std::string> getParamNames() const;
    std::map<std::string, AutoValue> getPreset(std::string const &) const;
	std::map<std::string, AutoValue> getPresetTemplate() const;
    void createPreset(std::string const &, std::map<std::string, AutoValue> const &);
    void updatePreset(std::string const &, std::map<std::string, AutoValue> const &);
    void removePreset(std::string const &);

	void setConnectionStrategy(ITableConnectionStrategy *);
};

#endif
