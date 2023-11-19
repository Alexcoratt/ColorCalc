/*
#include <cmath>

#include "IConnection.hpp"


class CompareFoilRolls {
private:
	IConnection const * _conn;
	double _minLength;
	double _minWidth;

	static constexpr double getWaste(double length, double width, double minLength, double minWidth) {
		double rollCount = minLength / length;
		double lengthWaste = (std::ceil(rollCount) - rollCount) * width;
		double widthWaste = (width - minWidth) * minLength;
		return lengthWaste + widthWaste;
	}

public:
	CompareFoilRolls(IConnection const * conn, double minLength, double minWidth) : _conn(conn), _minLength(minLength), _minWidth(minWidth) {}
	*/
	/*
	* comparing method
	* name being valued more when its roll prodused less waste
	*
	* if both rolls produses the same waste the most valued one is that
	* which requires less roll count
	*/
	/*
	bool operator()(std::string const & leftName, std::string const & rightName) {
		auto leftRoll = _conn->getFoilRollPreset(leftName);
		auto rightRoll = _conn->getFoilRollPreset(rightName);

		double lLength = std::stod(leftRoll.at("length"));
		double lWidth = std::stod(leftRoll.at("width"));

		double rLength = std::stod(rightRoll.at("length"));
		double rWidth = std::stod(rightRoll.at("width"));

		double lWaste = getWaste(lLength, lWidth, _minLength, _minWidth);
		double rWaste = getWaste(rLength, rWidth, _minLength, _minWidth);

		if (lWaste != rWaste)
			return lWaste < rWaste;
		return _minLength / lLength < _minLength / rLength;
	}
};

std::vector<std::string> IConnection::selectFoilRollPresets(double minLength, double minWidth) const {
	std::vector<std::string> res;
	auto rollNames = getFoilRollPresetNames();
	for (auto rollName : rollNames) {
		auto rollPreset = getFoilRollPreset(rollName);
		if (std::stod(rollPreset.at("width")) >= minWidth)
			res.push_back(rollName);
	}
	std::sort(res.begin(), res.end(), CompareFoilRolls(this, minLength, minWidth));
	return res;
};
*/
