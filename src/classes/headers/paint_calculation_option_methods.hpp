#ifndef PAINT_CALCULATION_OPTION_METHODS
#define PAINT_CALCULATION_OPTION_METHODS

#include <algorithm>
#include <exception>
#include <functional>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "IOption.hpp"
#include "PaintDataContainer.hpp"
#include "nlohmann/json.hpp"

#include "JsonValueIsNullException.hpp"
#include "DefaultOptionIsChosenExcepion.hpp"

#define PAINT_TYPE_COLUMN_NAME "тип краски"
#define MATERIAL_TYPE_COLUMN_NAME "тип материала"
#define PAINT_CONSUMPTION_COLUMN_NAME "расход краски"

#define PAINT_CALCULATION_TABLE_NAME "расчет печатной краски"

namespace paint_calculation_option_methods {

	inline std::string dump(nlohmann::json const & value, bool useQuotations = false) {
		if (value == nlohmann::json::value_t::null)
			return "undefined";
		if (useQuotations)
			return "\"" + value.dump() + "\"";
		return value.dump();
	}

	template <typename T>
	std::string toString(T value) { return std::to_string(value); }

	template <>
	inline std::string toString<std::string>(std::string value) { return value; }

	template <typename T>
	std::string getValue(std::function<T()> getValue, std::string const & defaultValue, bool useQuotations = false) {
		try {
			if (useQuotations)
				return "\"" + toString(getValue()) + "\"";
			return toString(getValue());
		} catch (JsonValueIsNullException const &) {
			return defaultValue;
		}
	}

	inline void writePrintParameters(IOption *, std::istream &, std::ostream & out, std::string const & endline, PaintDataContainer * container) {
		std::string const defaultValue = "undefined";

		std::map<std::string const, std::string const> const specialValues = {
			{container->getPresetNameColumnName(), getValue<std::string>([&](){ return container->getPresetName(); }, defaultValue, true)},
			{PAINT_TYPE_COLUMN_NAME, getValue<std::string>([&](){ return container->getPaintTypeName(); }, defaultValue, true)},
			{MATERIAL_TYPE_COLUMN_NAME, getValue<std::string>([&](){ return container->getMaterialTypeName(); }, defaultValue, true)},
			{PAINT_CONSUMPTION_COLUMN_NAME, getValue<double>([&](){ return container->getPaintConsumption(); }, defaultValue, false)}
		};

		out << "Parameters' values:" << endline;
		for (std::string const & column : container->getColumnsNames()) {
			std::string value;
			auto pair = specialValues.find(column);
			if (pair != specialValues.end())
				value = pair->second;
			else
				value = dump(container->getData(column));

			out << column << ":\t" << value << endline;
		}
	}

	template <typename T>
	T readValue(std::istream & in, std::function<T(std::string const &)> converter) {
		std::string line;
		std::getline(in, line);

		if (line == "")
			throw DefaultOptionIsChosenException();

		return converter(line);
	}

	inline std::size_t readIndexItem(std::istream & in, std::size_t itemCount) {
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

	inline void setValue(std::function<void()> intro, std::function<void()> prompt, std::function<void()> setItem, std::function<void(char const *)> printErrWhat, std::function<void()> outro) {
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

	inline void setPaintType(IOption *, std::istream & in, std::ostream & out, std::string const & endline, PaintDataContainer * container) {
		std::vector<std::string> types = container->getConnection()->getPaintTypes();

		std::string const defaultValue = getValue<std::string>([&](){ return std::to_string(container->getPaintTypeIndex() + 1); }, "undefined", true);

		setValue(
			[&]() {
				out << "Available paint types are" << endline;
				std::size_t count = 0;
				for (auto type : types)
					out << ++count << '\t' << type << endline;
				out << endline;

				out << "Current paint type value is " << defaultValue << endline << endline;
				in.ignore();
			},
			[&]() {
				out << "Enter option (default=" << defaultValue << "): ";
			},
			[&]() {
				container->setPaintType(readIndexItem(in, types.size()));
			},
			[&](char const * line) {
				out << line << endline;
			},
			[&]() {
				out << "Paint type " << getValue<std::string>([&](){ return container->getPaintTypeName(); }, "undefined", true) << " is set";
			}
		);
	}

	inline void setMaterialType(IOption *, std::istream & in, std::ostream & out, std::string const & endline, PaintDataContainer * container) {
		std::vector<std::string> types = container->getConnection()->getMaterialTypes();
		std::string const defaultValue = getValue<std::string>([&](){ return std::to_string(container->getMaterialTypeIndex() + 1); }, "undefined", true);

		setValue(
			[&]() {
				out << "Available material types are" << endline;
				std::size_t count = 0;
				for (auto type : types)
					out << ++count << '\t' << type << endline;
				out << endline;

				out << "Current material type value is " << defaultValue << endline << endline;
				in.ignore();
			},
			[&]() {
				out << "Enter option (default=" << defaultValue << "): ";
			},
			[&]() {
				container->setMaterialType(readIndexItem(in, types.size()));
			},
			[&](char const * line) {
				out << line << endline;
			},
			[&]() {
				out << "Material type " << getValue<std::string>([&](){ return container->getMaterialTypeName(); }, "undefined", true) << " is set";
			}
		);
	}

	template <typename T>
	void setValue(std::istream & in, std::ostream & out, std::string const & endline, std::string const & category, std::function<T()> getValue, std::function<void(T)> setValue, std::function<T(std::string const &)> converter, std::function<void(T)> checker) {
		std::string defaultValue;
		out << "Current " << category << " value is ";
		try {
			defaultValue = std::to_string(getValue());
			out << defaultValue;
		} catch (JsonValueIsNullException const &) {
			defaultValue = "undefined";
			out << defaultValue;
		}
		out << endline << endline;

		std::string const prompt = "Enter value (default=" + defaultValue + "): ";
		in.ignore();
		bool loop = true;
		while (loop) {
			try {
				out << prompt;
				T res = readValue<T>(in, converter);
				checker(res);
				setValue(res);
				loop = false;
			} catch (DefaultOptionIsChosenException const & err) {
				out << err.what() << endline;
				loop = false;
			} catch (std::invalid_argument const & err) {
				out << err.what() << endline;
			}
		}

		out << category << " value ";
		try {
			out << getValue() << " is set";
		} catch (JsonValueIsNullException const &) {
			out << "is undefined";
		}
		out << endline;
	}

	inline void setPaintConsumption(IOption *, std::istream & in, std::ostream & out, std::string const & endline, PaintDataContainer * container) {
		setValue<double>(in, out, endline, "paint consumption",
			[&](){ return container->getPaintConsumption(); },
			[&](double value){ container->setPaintConsumption(value); },
			[](std::string const & line){ return std::stod(line); },
			[](double value) {
				if (value <= 0)
					throw std::invalid_argument("Value must be greater than 0");
			}
		);
	}

	inline void setDivider(IOption *, std::istream & in, std::ostream & out, std::string const & endline, PaintDataContainer * container) {
		setValue<double>(in, out, endline, "divider",
			[&](){ return container->getDivider(); },
			[&](double value){ container->setDivider(value); },
			[](std::string const & line){ return std::stod(line); },
			[](double value) {
				if (value <= 0)
					throw std::invalid_argument("Value must be greater than 0");
			}
		);
	}

	inline void setPercent(IOption *, std::istream & in, std::ostream & out, std::string const & endline, PaintDataContainer * container) {
		setValue<double>(in, out, endline, "print percent",
			[&](){ return container->getPercent(); },
			[&](double value){ container->setPercent(value); },
			[](std::string const & line){ return std::stod(line); },
			[](double value) {
				if (value <= 0 || value > 100)
					throw std::invalid_argument("Value must be greater than 0 and must not exceed 100");
			}
		);
	}

	inline void setWidth(IOption *, std::istream & in, std::ostream & out, std::string const & endline, PaintDataContainer * container) {
		setValue<double>(in, out, endline, "sheet width",
			[&](){ return container->getWidth(); },
			[&](double value){ container->setWidth(value); },
			[](std::string const & line){ return std::stod(line); },
			[](double value) {
				if (value <= 0)
					throw std::invalid_argument("Value must be greater than 0");
			}
		);
	}

	inline void setLength(IOption *, std::istream & in, std::ostream & out, std::string const & endline, PaintDataContainer * container) {
		setValue<double>(in, out, endline, "sheet length",
			[&](){ return container->getLength(); },
			[&](double value){ container->setLength(value); },
			[](std::string const & line){ return std::stod(line); },
			[](double value) {
				if (value <= 0)
					throw std::invalid_argument("Value must be greater than 0");
			}
		);
	}

	inline void setCirculation(IOption *, std::istream & in, std::ostream & out, std::string const & endline, PaintDataContainer * container) {
		setValue<std::size_t>(in, out, endline, "circulation",
			[&](){ return container->getCirculation(); },
			[&](std::size_t value){ container->setCirculation(value); },
			[](std::string const & line){ return std::stoul(line); },
			[](std::size_t value) {
				if (value <= 0)
					throw std::invalid_argument("Value must be greater than 0");
			}
		);
	}

	inline void setPaintReserve(IOption *, std::istream & in, std::ostream & out, std::string const & endline, PaintDataContainer * container) {
		setValue<double>(in, out, endline, "paint reserve",
			[&](){ return container->getPaintReserve(); },
			[&](double value){ container->setPaintReserve(value); },
			[](std::string const & line){ return std::stod(line); },
			[](double value) {
				if (value <= 0)
					throw std::invalid_argument("Value must be greater than 0");
			}
		);
	}

	inline void loadPreset(IOption *, std::istream & in, std::ostream & out, std::string const & endline, PaintDataContainer * container) {
		IConnection * conn = container->getConnection();
		std::vector<std::string> presets = conn->getPresetsNames( PAINT_CALCULATION_TABLE_NAME);

		std::string const defaultValue = getValue<std::string>([&](){ return std::to_string(conn->getPresetIndex(PAINT_CALCULATION_TABLE_NAME, container->getPresetName()) + 1); }, "undefined", true);

		setValue(
			[&]() {
				out << "Available presets are" << endline;
				std::size_t count = 0;
				for (auto preset : presets)
					out << ++count << '\t' << preset << endline;
				out << endline;

				out << "Current value is " << defaultValue << endline << endline;
				in.ignore();
			},
			[&]() {
				out << "Enter option (default=" << defaultValue << "): ";
			},
			[&]() {
				container->setPreset(presets[readIndexItem(in, presets.size())]);
			},
			[&](char const * line) {
				out << line << endline;
			},
			[&]() {
				out << "Preset " << getValue<std::string>([&](){ return container->getPresetName(); }, "undefined", true) << " is set";
			}
		);
	}

	inline bool readSubmit(std::istream & in, std::ostream & out, std::string const & endline, std::string const & message) {
		std::vector<std::string> const answers = {"yes", "no"};
		std::string const defaultValue = "2";
		bool res = false;

		setValue(
			[&]() {
				out << message << endline << 1 << '\t' << "yes" << endline << 2 << '\t' << "no" << endline << endline;
				in.ignore();
			},
			[&]() {
				out << "Enter option (default=" << defaultValue << "): ";
			},
			[&]() {
				if (readIndexItem(in, 2) == 0)
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

	inline void clearValues(IOption *, std::istream & in, std::ostream & out, std::string const & endline, PaintDataContainer * container) {
		if (readSubmit(in, out, endline, "Are you surely want to clear all values?"))
			container->clearData();
	}

	template <typename T>
	bool isIn(std::vector<T> const & vect, T search) {
		for (T value : vect)
			if (value == search)
				return true;
		return false;
	}

	inline void calculatePaintAmount(IOption *, std::istream & in, std::ostream & out, std::string const & endline, PaintDataContainer * container) {
		try {
			PaintDataContainer * c = container;
			double res = c->getWidth() * c->getLength() / 1000000 * c->getPaintConsumption() / 1000 / c->getDivider() * c->getCirculation() * c->getPercent() / 100 + c->getPaintReserve();
			out << "Paint amount equals " << res << "kg" << endline;
		} catch (JsonValueIsNullException const & err) {
			out << err.what() << endline;
		}
	}
}

#endif
