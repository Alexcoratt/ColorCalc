#ifndef BASE_TABLE_HPP
#define BASE_TABLE_HPP

#include "ITable.hpp"

struct IValueLess {
	inline bool operator()(IValue const & l, IValue const & r) const {
		try {
			return l.less(&r);
		} catch (std::exception const &) {
			return true;
		}
	}
};

class BaseTable : public ITable {
private:
	std::vector<AutoValue> _rowHeadings;
	std::vector<AutoValue> _columnHeadings;
	std::map<AutoValue, std::map<AutoValue, AutoValue, IValueLess>, IValueLess> _values;

public:
	BaseTable(std::vector<AutoValue> const &, std::vector<AutoValue> const &);
	BaseTable(BaseTable const &);
	BaseTable & operator=(BaseTable const &);
	~BaseTable();
	void swap(BaseTable &);

	void setValue(AutoValue const &, AutoValue const &, AutoValue const &);
	void insertRow(AutoValue const &, AutoValue const &, std::vector<AutoValue> const &);
	void insertColumn(AutoValue const &, AutoValue const &, std::vector<AutoValue> const &);
	void appendRow(AutoValue const &, std::vector<AutoValue> const &);
	void appendColumn(AutoValue const &, std::vector<AutoValue> const &);

	std::vector<AutoValue> getRowHeadings() const;
	std::vector<AutoValue> getColumnHeadings() const;

	AutoValue getValue(AutoValue const &, AutoValue const &) const;
	AutoValue & getValueLink(AutoValue const &, AutoValue const &);

	std::string toString() const;
};

#endif
