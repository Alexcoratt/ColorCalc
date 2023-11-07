#ifndef BASE_TABLE_HPP
#define BASE_TABLE_HPP

#include "ITable.hpp"

struct IValueLess {
	inline bool operator()(IValue const * l, IValue const * r) const {
		try {
			return l->less(r);
		} catch (std::exception const &) {
			return true;
		}
	}
};

class BaseTable : public ITable {
private:
	std::vector<IValue *> _rowHeadings;
	std::vector<IValue *> _columnHeadings;
	std::map<IValue *, std::map<IValue *, IValue *, IValueLess>, IValueLess> _values;

public:
	BaseTable(std::vector<IValue *> const &, std::vector<IValue *> const &);
	BaseTable(BaseTable const &);
	BaseTable & operator=(BaseTable const &);
	~BaseTable();
	void swap(BaseTable &);

	void setValue(IValue const *, IValue const *, IValue *);


	std::vector<IValue const *> getRowHeadings() const;
	std::vector<IValue const *> getColumnHeadings() const;

	IValue const * getValue(IValue const *, IValue const *) const;
	IValue * getValuePointer(IValue const *, IValue const *);

	std::string toString() const;
};

#endif
