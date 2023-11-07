#ifndef QUIT_OPTION_HPP
#define QUIT_OPTION_HPP

#include <vector>
#include <string>
#include <functional>

#include "IOption.hpp"
#include "DefaultOptionIsChosenExcepion.hpp"
#include "OptionQuitException.hpp"

class QuitOption : public IOption {
private:
	template <typename T>
	T readValue(std::istream & in, std::function<T(std::string const &)> converter) {
		std::string line;
		std::getline(in, line);

		if (line == "")
			throw DefaultOptionIsChosenException();

		return converter(line);
	}

	std::size_t readIndexItem(std::istream & in, std::size_t itemCount) {
		return readValue<std::size_t>(
			in,
			[&](std::string const & line) {
				try {
					std::size_t value = std::stoul(line) - 1;
					if (value < itemCount)
						return value;
				} catch (std::invalid_argument const &) {}
				throw std::invalid_argument("No such option \"" + line + "\"");
			}
		);
	}

	void setValue(std::function<void()> intro, std::function<void()> prompt, std::function<void()> setItem, std::function<void(char const *)> printErrWhat, std::function<void()> outro) {
		intro();
		bool loop = true;
		while (loop) {
			try {
				prompt();
				setItem();
				loop = false;
			} catch (DefaultOptionIsChosenException const & err) {
				printErrWhat(err.what());
				loop = false;
			} catch (std::invalid_argument const & err) {
				printErrWhat(err.what());
			}
		}
		outro();
	}

	bool readSubmit(std::istream & in, std::ostream & out, std::string const & endline, std::string const & message) {
		std::vector<std::string> const answers = {"no", "yes"};
		std::string const defaultValue = "1";
		bool res = false;

		setValue(
			[&]() {
				out << message << endline << 1 << '\t' << "no" << endline << 2 << '\t' << "yes" << endline << endline;
				in.ignore();
			},
			[&]() {
				out << "Enter option (default=" << defaultValue << "): ";
			},
			[&]() {
				if (readIndexItem(in, 2) == 1)
					res = true;
			},
			[&](char const * line) {
				out << line << endline;
			},
			[&]() {
				if (res)
					out << "Submitted" << endline;
				else
					out << "Cancelled" << endline;
			}
		);

		return res;
	}

public:
	inline void exec(IOption *, std::istream & in, std::ostream & out, std::string const & endline) {
		if (readSubmit(in, out, endline, "Are you really want to exit?"))
			throw new OptionQuitException;
	}

	inline std::string getName() const { return "quit"; }
	inline std::string getHelp() const { return "Ends the program"; }
};

#endif
