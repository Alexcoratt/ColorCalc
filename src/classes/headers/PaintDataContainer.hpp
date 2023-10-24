#ifndef PAINT_DATA_CONTAINER_HPP
#define PAINT_DATA_CONTAINER_HPP

#include <string>
#include "IConnection.hpp"

class PaintDataContainer {
private:
	IConnection * _conn;	// input value
	nlohmann::json _data;	// input/output value
	std::string _presetNameColumnName;

public:
	PaintDataContainer(IConnection *);

	IConnection * getConnection() const;
	std::string getPresetNameColumnName() const;
	std::vector<std::string> getColumnsNames() const;
	nlohmann::json getData() const;
	nlohmann::json getData(std::string const &) const;
	void setData(std::string const &, nlohmann::json const &);

	std::string getPresetName() const;
	void setPresetName(std::string const &);
	void clearPresetName();

	std::size_t getPaintTypeIndex() const;
	std::string getPaintTypeName() const;
	void setPaintType(std::size_t);
	void setPaintType(std::string);
	void clearPaintType();

	std::size_t getMaterialTypeIndex() const;
	std::string getMaterialTypeName() const;
	void setMaterialType(std::size_t);
	void setMaterialType(std::string);
	void clearMaterialType();

	double getPaintConsumption() const;
	void setPaintConsumption(double);
	void clearPaintConsumption();

	double getDivider() const;
	void setDivider(double);
	void clearDivider();

	double getPercent() const;
	void setPercent(double);
	void clearPercent();

	double getWidth() const;
	void setWidth(double);
	void clearWidth();

	double getLength() const;
	void setLength() const;
	void clearLength();

	std::size_t getCirculation() const;
	void setCirculation(std::size_t);
	void clearCirculation();

	double getReserve() const;
	void setReserve(double) const;
	void clearReserve();
};

#endif
