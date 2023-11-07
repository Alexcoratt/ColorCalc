#ifndef I_TABLE_HPP
#define I_TABLE_HPP

#include <vector>
#include "IValue.hpp"

class ITable {
public:
	virtual void setValue(IValue const *, IValue const *, IValue *) = 0;
	virtual void insertRow(IValue const *, IValue const *, std::vector<IValue *> const &) = 0;
	virtual void insertColumn(IValue const *, IValue const *, std::vector<IValue *> const &) = 0;
	virtual void appendRow(IValue const *, std::vector<IValue *> const &) = 0;
	virtual void appendColumn(IValue const *, std::vector<IValue *> const &) = 0;

	virtual std::vector<IValue const *> getRowHeadings() const = 0;
	virtual std::vector<IValue const *> getColumnHeadings() const = 0;

	virtual IValue const * getValue(IValue const *, IValue const *) const = 0;
	virtual IValue * getValuePointer(IValue const *, IValue const *) = 0;

	virtual std::vector<IValue const *> getRow(IValue const *) const = 0;
	virtual std::vector<IValue const *> getColumn(IValue const *) const = 0;

	virtual std::string toString() const = 0;
};

#endif
