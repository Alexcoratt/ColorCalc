#ifndef FOIL_DATA_DISPATCHER_HPP
#define FOIL_DATA_DISPATCHER_HPP

#include "AbstractDataDispatcher.hpp"
#include "IConnection.hpp"

class FoilDataDispatcher : public AbstractDataDispatcher {
private:
	IConnection * _conn;
	std::map<std::string, AutoValue> _params;
	std::string _presetName;

public:
	FoilDataDispatcher(IConnection *);

	IConnection * getConnection();

	std::vector<std::string> getAvailablePresetNames() const;
	std::vector<std::string> getParamNames() const;
	std::map<std::string, std::string> toStringMap() const;

	void clear();

	std::string getPresetName() const;
	void setPreset(std::string const &);

	void createPreset(std::string const &);
	void updatePreset(std::string const &);
	void removePreset(std::string const &);

	std::size_t getCirculation() const;
	void setCirculation(std::size_t const &);

	double getLength() const;
	void setLength(double);

	std::size_t getSheetNumber() const;
	void setSheetNumber(std::size_t const &);

	double getWidthReserve() const;
	void setWidthReserve(double);

	double calculate() const;
};

#endif
