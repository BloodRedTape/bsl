#pragma once

#include "utils/format.hpp"

enum Verbosity {
	Display,
	Info,
	Warning,
	Error,
	Fatal
};

inline std::ostream& operator<<(std::ostream& stream, Verbosity verbosity) {
	switch (verbosity)
	{
	case Verbosity::Display:
		stream << "Display";
		break;
	case Verbosity::Info:
		stream << "Info";
		break;
	case Verbosity::Warning:
		stream << "Warning";
		break;
	case Verbosity::Error:
		stream << "Error";
		break;
	case Verbosity::Fatal:
		stream << "Fatal";
		break;
	}
	return stream;
}

template<typename...ArgsType>
void Log(Verbosity verbosity, const char* fmt, ArgsType...args) {
	auto &stream = (verbosity == Fatal || verbosity == Error) ? std::cerr : std::cout;

	StreamFormat(stream, "[%]: %\n", verbosity, Format(fmt, args...));
}

#define DEFINE_LOG_CATEGORY(name) \
template<typename...ArgsType> \
static void Log##name(Verbosity verbosity, const char* fmt, ArgsType...args) { \
	auto &stream = (verbosity == Fatal || verbosity == Error) ? std::cerr : std::cout; \
	StreamFormat(stream, "[%][%]: %\n", #name, verbosity, Format(fmt, args...)); \
} \
template<typename...ArgsType> \
static void Log##name##If(bool condition, Verbosity verbosity, const char *fmt, ArgsType...args) {\
	if(condition) Log##name(verbosity, fmt, args...); \
}
