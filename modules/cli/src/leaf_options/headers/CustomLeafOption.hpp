#ifndef CUSTOM_LEAF_OPTION_HPP
#define CUSTOM_LEAF_OPTION_HPP

#include "IOption.hpp"
#include <functional>

template <typename T>
inline std::function<void(IOption *, std::istream &, std::ostream &, std::string const &, T)> getProxyFunc(std::function<void(T)> const & func) {
	return [=](IOption *, std::istream &, std::ostream &, std::string const &, T data) { func(data); };
}

template <typename T>
class CustomLeafOption : public IOption {
private:
	std::string _name;
	std::string _help;
	std::function<void(IOption *, std::istream &, std::ostream &, std::string const &, T)> _func;
	T _data;

public:
	CustomLeafOption(std::string const & name, std::string const & help, std::function<void(IOption *, std::istream &, std::ostream &, std::string const &, T)> const & func, T data) : _name(name), _help(help), _func(func), _data(data) {}

	CustomLeafOption(std::string const & name, std::string const & help, std::function<void(T)> const & func, T data) : _name(name), _help(help), _func(getProxyFunc(func)), _data(data) {}

	void setData(T data) { _data = data; }
	T getData() const { return _data; }

	void exec(IOption * parent, std::istream & input, std::ostream & output, std::string const & endline) { _func(parent, input, output, endline, _data); }

	std::string getName() const { return _name; }
	std::string getHelp() const { return _help; }
};


template <>
class CustomLeafOption<void> : public IOption {
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
