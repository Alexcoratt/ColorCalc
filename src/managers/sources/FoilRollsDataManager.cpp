#include <cmath>

#include "FoilRollsDataManager.hpp"
#include "auxillary_methods.hpp"

#define LENGTH "length"
#define WIDTH "width"

FoilRollsDataManager::FoilRollsDataManager(ITableConnection * conn) {
	setConnection(conn);
	importData(conn->getPresetTemplate());
}

void FoilRollsDataManager::importData(std::map<std::string, AutoValue> const & params) {
	auxillary_methods::setParam(_length, params, LENGTH);
	auxillary_methods::setParam(_width, params, WIDTH);
}

std::map<std::string, AutoValue> FoilRollsDataManager::exportData() const {
	std::map<std::string, AutoValue> res;
	auxillary_methods::setMapValue(res, _length);
	auxillary_methods::setMapValue(res, _width);
	return res;
}

void FoilRollsDataManager::clear() {
	_name.clear();
	_length.clear();
	_width.clear();
}

void FoilRollsDataManager::setName(std::string const & name) { _name = name; }
void FoilRollsDataManager::clearName() { _name.clear(); }
std::string FoilRollsDataManager::getName() const { return _name; }

double FoilRollsDataManager::calculate() const { throw std::runtime_error("FoilRollDataDispatcher does no calculations"); }

double FoilRollsDataManager::getLength() const { return _length; }
void FoilRollsDataManager::setLength(double value) {
	if (_length == value)
		return;

	_length = value;
	_name.clear();
}

void FoilRollsDataManager::clearLength() {
	if (!_length.isDefined())
		return;

	_length.clear();
	_name.clear();
}

double FoilRollsDataManager::getWidth() const { return _width; }
void FoilRollsDataManager::setWidth(double value) {
	if (_width == value)
		return;

	_width = value;
	_name.clear();
}

void FoilRollsDataManager::clearWidth() {
	if (!_width.isDefined())
		return;

	_width.clear();
	_name.clear();
}

// class created for comparing foil rolls using std::sort
class CompareFoilRolls {
private:
	ITableConnection const * _conn;
	double _minLength;
	double _minWidth;

	static constexpr double getWaste(double length, double width, double minLength, double minWidth) {
		double rollCount = minLength / length;
		double lengthWaste = (std::ceil(rollCount) - rollCount) * width;
		double widthWaste = (width - minWidth) * minLength;
		return lengthWaste + widthWaste;
	}

public:
	CompareFoilRolls(ITableConnection const * conn, double minLength, double minWidth) : _conn(conn), _minLength(minLength), _minWidth(minWidth) {}
	/*
	* comparing method
	* name being valued more when its roll prodused less waste
	*
	* if both rolls produses the same waste the most valued one is that
	* which requires less roll count
	*/
	bool operator()(std::string const & leftName, std::string const & rightName) {
		auto leftRoll = _conn->getPreset(leftName);
		auto rightRoll = _conn->getPreset(rightName);

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

std::vector<std::string> FoilRollsDataManager::getSuitableFoilRolls(double minLength, double minWidth) const {
	std::vector<std::string> res;
	auto rollNames = getConnection()->getPresetNames();
	for (auto rollName : rollNames) {
		auto rollPreset = getConnection()->getPreset(rollName);
		if (rollPreset.at("width") >= AutoValue(minWidth))
			res.push_back(rollName);
	}
	std::sort(res.begin(), res.end(), CompareFoilRolls(getConnection(), minLength, minWidth));
	return res;
}
