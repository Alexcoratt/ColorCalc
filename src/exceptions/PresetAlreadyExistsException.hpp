#ifndef PRESET_ALREADY_EXISTS_EXCEPTION_HPP
#define PRESET_ALREADY_EXISTS_EXCEPTION_HPP

#include <exception>
#include <string>

class PresetAlreadyExistsException : public std::exception {
private:
	std::string _msg;

public:
	inline PresetAlreadyExistsException(std::string const & name) : _msg("Preset named \"" + name + "\" already exists") {}

	inline char const * what() const noexcept { return _msg.c_str(); }
};

#endif
