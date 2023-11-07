#include "IOption.hpp"
#include "BaseOptionContainer.hpp"
#include "CustomLeafOption.hpp"

void printParentName(IOption * parent, std::istream & input, std::ostream & output, std::string const & endline) {
	output << parent->getName() << endline;
}

void printNumber(IOption *, std::istream &, std::ostream & output, std::string const & endline, int num) {
	output << num << endline;
}

void printInput(IOption *, std::istream & input, std::ostream & output, std::string const & endline) {
	std::string str;
	input >> str;
	output << str << endline;
}

void sum(std::pair<double, double> const & values) {
	std::cout << values.first + values.second << std::endl;
}

int main() {

	IOption * ppn = new CustomLeafOption<void>("get parent name", "prints parent's name", printParentName);
	CustomLeafOption<int> * pn = new CustomLeafOption<int>("print a number", "prints some number", printNumber, 32);
	IOption * pi = new CustomLeafOption<void>("print input", "prints the user\'s input", printInput);
	CustomLeafOption<std::pair<double, double> const &> sm("print sum", "Prints sum of two values", sum, {0.5, 3.2});

	BaseOptionContainer * container1 = new BaseOptionContainer("first container", BASE_HELP_TEXT, { {'p', ppn}, {'s', &sm} });
	BaseOptionContainer * container2 = new BaseOptionContainer("second container");
	BaseOptionContainer * container3 = new BaseOptionContainer("third container");

	try {
		BaseOptionContainer * rootContainer = new BaseOptionContainer("root container", BASE_HELP_TEXT, { {'c', container1} }, true);

		container1->addOption('c', container2);
		container2->addOption('c', container3);

		rootContainer->addOption('n', pn);
		container2->addOption('i', pi);
		container3->addOption('n', pn);

		pn->setData(-12);

		rootContainer->exec(0, std::cin, std::cout, "\n");

		delete rootContainer;
	} catch (std::exception const * err) {
		std::cerr << err->what() << std::endl;
		delete err;
	}

	delete container1;
	delete container2;
	delete container3;

	delete ppn;
	delete pn;
	delete pi;

	return 0;
}
