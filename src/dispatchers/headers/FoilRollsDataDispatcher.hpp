#ifndef FOIL_ROLLS_DATA_DISPATCHER_HPP
#define FOIL_ROLLS_DATA_DISPATCHER_HPP

#include <AbstractDataDispatcher.hpp>

class FoilRollsDataDispatcher : public AbstractDataDispatcher {
private:
	IConnection * _conn;
	std::map<std::string, AutoValue> _params;
	std::string _presetName;

public:
	FoilRollsDataDispatcher(IConnection *);

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

	double calculate() const;

	double getLength() const;
	void setLength(double);

	double getWidth() const;
	void setWidth(double);
};

#endif
