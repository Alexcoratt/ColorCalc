#ifndef CUSTOM_LEAF_OPTION_HPP
#define CUSTOM_LEAF_OPTION_HPP

#include "AbstractLeafOption.hpp"
#include <functional>

template <typename T>
class CustomLeafOption : public AbstractLeafOption {
private:
	std::string _name;
	std::string _help;
	std::function<void(IOption *, std::istream &, std::ostream &, std::string const &, int)> const & _func;
	T _data;

public:
	CustomLeafOption(std::string const &, std::string const &, std::function<void(IOption *, std::istream &, std::ostream &, std::string const &, T)> const &, T);

	void setData(T);
	T getData() const;

	void exec(IOption *, std::istream &, std::ostream &, std::string const &);
	std::string getName() const;
	std::string getHelp() const;
};


template <typename T>
CustomLeafOption<T>::CustomLeafOption(std::string const & name, std::string const & help, std::function<void(IOption *, std::istream &, std::ostream &, std::string const &, T)> const & func, T data) : _name(name), _help(help), _func(func), _data(data) {}

template <typename T>
void CustomLeafOption<T>::setData(T data) { _data = data; }

template <typename T>
T CustomLeafOption<T>::getData() const { return _data; }

template <typename T>
void CustomLeafOption<T>::exec(IOption * parent, std::istream & input, std::ostream & output, std::string const & endline) {
	_func(parent, input, output, endline, _data);
}

template <typename T>
std::string CustomLeafOption<T>::getName() const { return _name; }

template <typename T>
std::string CustomLeafOption<T>::getHelp() const { return _help; }


template <>
class CustomLeafOption<void> : public AbstractLeafOption {
private:
	std::string _name;
	std::string _help;
	std::function<void(IOption *, std::istream &, std::ostream &, std::string const &)> const & _func;

public:
	CustomLeafOption(std::string const & name, std::string const & help, std::function<void(IOption *, std::istream &, std::ostream &, std::string const &)> const & func) : _name(name), _help(help), _func(func) {}

	void exec(IOption * parent, std::istream & input, std::ostream & output, std::string const & endline) {
		_func(parent, input, output, endline);
	}

	std::string getName() const { return _name; }
	std::string getHelp() const { return _help; }
};

#endif
