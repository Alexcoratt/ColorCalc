#include <iostream>
#include <string>

#include <AutoValue.hpp>
#include <StringValue.hpp>
#include <SmartPointer.hpp>
#include <NullValue.hpp>

int main() {
	AutoValue a = 3;
	AutoValue b = "Hello";
	AutoValue c;

	std::cout << a << ' ' << b << ' ' << c << std::endl;

	a = "World";
	std::cout << a << ' ';

	b = 2.43;
	std::cout << b << ' ';

	c = -21.32;
	std::cout << c << ' ';

	SmartPointer<AutoValue> aClone = a.getClone();

	std::cout << std::endl << a.nestCount() << ' ' << *aClone << std::endl;

	AutoValue n;
	std::cout << (n = NullValue()).isNull() << std::endl;

	return 0;
}
