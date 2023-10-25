#ifndef PAINT_DATA_CONTAINER_HPP
#define PAINT_DATA_CONTAINER_HPP

#include <string>
#include "IConnection.hpp"

class PaintDataContainer {
private:
	IConnection * _conn;	// input value
	nlohmann::json _data;	// input/output value
	std::string _presetNameColumnName;

	template <typename T>
	T getValue(std::string const &) const;

	template <typename T>
	void setValue(std::string const &, T value);

	void clear(std::string const &);

public:
	PaintDataContainer(IConnection *);

	IConnection * getConnection() const;
	std::string getPresetNameColumnName() const;
	std::vector<std::string> getColumnsNames() const;
	nlohmann::json getData() const;
	nlohmann::json getData(std::string const &) const;
	void setData(std::string const &, nlohmann::json const &);

	void clearData();

	std::string getPresetName() const;
	void setPreset(std::size_t);
	void setPreset(std::string const &);

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

	double getDivider() const;
	void setDivider(double);

	double getPercent() const;
	void setPercent(double);

	double getWidth() const;
	void setWidth(double);

	double getLength() const;
	void setLength(double);

	std::size_t getCirculation() const;
	void setCirculation(std::size_t);

	double getPaintReserve() const;
	void setPaintReserve(double);
};

#endif
