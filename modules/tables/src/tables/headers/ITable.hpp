#ifndef I_TABLE_HPP
#define I_TABLE_HPP

#include <vector>
#include "AutoValue.hpp"

class ITable {
public:
	virtual void setValue(AutoValue const &, AutoValue const &, AutoValue const &) = 0;
	virtual void insertRow(AutoValue const &, AutoValue const &, std::vector<AutoValue> const &) = 0;
	virtual void insertColumn(AutoValue const &, AutoValue const &, std::vector<AutoValue> const &) = 0;
	virtual void appendRow(AutoValue const &, std::vector<AutoValue> const &) = 0;
	virtual void appendColumn(AutoValue const &, std::vector<AutoValue> const &) = 0;

	virtual std::vector<AutoValue> getRowHeadings() const = 0;
	virtual std::vector<AutoValue> getColumnHeadings() const = 0;

	virtual AutoValue getValue(AutoValue const &, AutoValue const &) const = 0;
	virtual AutoValue & getValueLink(AutoValue const &, AutoValue const &) = 0;

	virtual std::vector<AutoValue> getRow(AutoValue const &) const = 0;
	virtual std::vector<AutoValue> getColumn(AutoValue const &) const = 0;

	virtual std::string toString() const = 0;
};

#endif
