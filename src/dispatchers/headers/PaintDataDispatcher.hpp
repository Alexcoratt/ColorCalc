#ifndef PAINT_DATA_DISPATCHER_HPP
#define PAINT_DATA_DISPATCHER_HPP

#include <AutoValue.hpp>

#include "AbstractDataDispatcher.hpp"
#include "IConnection.hpp"

class PaintDataDispatcher : public AbstractDataDispatcher {
private:
	IConnection * _conn;
	std::map<std::string, AutoValue> _params;
	std::string _presetName;

public:
	PaintDataDispatcher(IConnection *);

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

	std::string getPaintType() const;
	void setPaintType(std::string const &);

	std::string getMaterialType() const;
	void setMaterialType(std::string const &);

	double getPaintConsumption() const;
	void setPaintConsumption(double);

	double getDivider() const;
	void setDivider(double);

	double getPercentage() const;
	void setPercentage(double);

	double getSheetWidth() const;
	void setSheetWidth(double);

	double getSheetLength() const;
	void setSheetLength(double);

	std::size_t getCirculation() const;
	void setCirculation(std::size_t const &);

	double getPaintReserve() const;
	void setPaintReserve(double);

	double calculate() const;
};

#endif
