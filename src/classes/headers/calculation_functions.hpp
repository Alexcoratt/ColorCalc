#ifndef CALCULATION_FUNCTIONS_HPP
#define CALCULATION_FUNCTIONS_HPP

#include "IConnection.hpp"
#include "json.hpp"

// all data must be provided in the same system's units (meters and kilograms)
// printRatio is a percent value divided by 100
inline double calculatePaintAmount(double paintConsumption, double divider, double multiplier, double printRatio, double sheetSquare, unsigned long circulation, double reserve) {
	return paintConsumption / divider * printRatio * sheetSquare * circulation * multiplier + reserve;
}
// use json data to execute calculatePaintAmount with preprocessed data
inline double calculatePaintAmount(IConnection const * conn, nlohmann::json const & preset) {
	return calculatePaintAmount(
		conn->getPaintConsumption(std::size_t(preset["тип краски"]), std::size_t(preset["материал"])) / 1000,
		preset["делитель"],
		preset["множитель"],
		double(preset["процент запечатки"]) / 100,
		double(preset["ширина печатного листа"]) * double(preset["длина печатного листа"]) / 1000000,
		preset["тираж"],
		preset["запас краски"]
	);
}

// all data must be provided in the same system's units (meters and kilograms)
// ratio is a percent value divided by 100
inline double calculateLacquerAmount(double lacquerConsumption, double ratio, double square, unsigned long circulation) {
	return lacquerConsumption * ratio * square * circulation;
}

inline double calculateLacquerAmount(nlohmann::json const & preset) {
	return calculateLacquerAmount(
		double(preset["расход лака"]) / 1000,
		double(preset["процент заливки"]) / 100,
		double(preset["длина"]) * double(preset["ширина"]) / 1000000,
		preset["тираж"]
	);
}

#endif
