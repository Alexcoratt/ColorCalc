#ifndef PAINT_DATA_CONTAINER_HPP
#define PAINT_DATA_CONTAINER_HPP

#include <string>
#include "IConnection.hpp"

class PaintDataContainer {
private:
	IConnection * _conn;
	std::string _presetName;
	nlohmann::json _data;

	template <typename T>
	T getValue(std::string const &) const;

	template <typename T>
	void setValue(std::string const &, T value);

	void clear(std::string const &);

public:
	PaintDataContainer(IConnection *);

	IConnection * getConnection() const;
	std::vector<std::string> getColumns() const;

	void clearData();

	std::string getPresetName() const;
	void setPreset(std::string const &);

	std::string getPaintType() const;
	void setPaintType(std::string);

	std::string getMaterialType() const;
	void setMaterialType(std::string);

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
