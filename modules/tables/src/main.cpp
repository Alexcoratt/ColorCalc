#include <iostream>

#include "AutoValue.hpp"

int main() {
	AutoValue a = 3;
	AutoValue b = "Hello";
	AutoValue c;

	std::cout << a.toString() << ' ' << b.toString() << ' ' << c.toString() << std::endl;

	a = "World";
	b = 2.43;
	c = -21.32;

	std::cout << a.toString() << ' ' << b.toString() << ' ' << c.toString() << std::endl;

	return 0;
}
