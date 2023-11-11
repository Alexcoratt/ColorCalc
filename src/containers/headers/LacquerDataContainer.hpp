#ifndef LACQUER_DATA_CONTAINER_HPP
#define LACQUER_DATA_CONTAINER_HPP

#include "IConnection.hpp"
#include "AbstractDataContainer.hpp"

class LacquerDataContainer : public AbstractDataContainer {
private:
	IConnection * _conn;
	std::map<std::string, AutoValue> _params;
	AutoValue _presetName;

public:
	LacquerDataContainer(IConnection *);

	IConnection * getConnection() const;

	std::vector<std::string> getParamNames() const;
	std::map<std::string, std::string> toStringMap() const;

	void clear();

	std::string getPresetName() const;
	void setPreset(std::string const &);

	double getPercentage() const;
	void setPercentage(double);

	double getLacquerConsumption() const;
	void setLacquerConsumption(double);

	double getSheetLength() const;
	void setSheetLength(double);

	double getSheetWidth() const;
	void setSheetWidth(double);

	std::size_t getCirculation() const;
	void setCirculation(std::size_t);

	double calculate() const;
};

#endif
