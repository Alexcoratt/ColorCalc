#include <iostream>
#include <string>

#include "AutoValue.hpp"

std::ostream & operator<<(std::ostream & stream, IValue const & value) {
	stream << std::string(value);
	return stream;
}

int main() {
	AutoValue a = 3;
	AutoValue b = "Hello";
	AutoValue c;

	std::cout << a << ' ' << b << ' ' << c << std::endl;

	a = "World";
	b = 2.43;
	c = -21.32;

	std::cout << a << ' ' << b << ' ' << c << std::endl;

	return 0;
}
