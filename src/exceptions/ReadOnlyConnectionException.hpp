#ifndef READ_ONLY_CONNECTION_EXCEPTION_HPP
#define READ_ONLY_CONNECTION_EXCEPTION_HPP

#include <stdexcept>
#include <string>
#include <ITableConnection.hpp>

class ReadOnlyConnectionException : public std::exception {
private:
	std::string _msg;

public:
	ReadOnlyConnectionException(ITableConnection const * conn) : _msg("This connection is read only :\n" + conn->getName()) {}
	ReadOnlyConnectionException(std::string const & connName) : _msg("This connection is read only :\n" + connName) {}

	char const * what() const noexcept { return _msg.c_str(); }
};

#endif
