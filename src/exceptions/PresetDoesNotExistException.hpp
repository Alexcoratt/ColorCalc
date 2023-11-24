#ifndef PRESET_DOES_NOT_EXIST_EXCEPTION_HPP
#define PRESET_DOES_NOT_EXIST_EXCEPTION_HPP

#include <exception>
#include <string>

class PresetDoesNotExistException : public std::exception {
private:
	std::string _msg;

public:
	inline PresetDoesNotExistException(std::string const & name) : _msg("Preset named \"" + name + "\" does not exist") {}

	inline char const * what() const noexcept { return _msg.c_str(); }
};

#endif
