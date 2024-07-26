#pragma once

#include "bsl/format.hpp"

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

#ifndef BSL_WITH_EXTERNAL_LOG_FUNCTION
	#define BSL_WITH_EXTERNAL_LOG_FUNCTION 0
#endif

#if BSL_WITH_EXTERNAL_LOG_FUNCTION
extern void LogFunctionExternal(const std::string &category, Verbosity verbosity, const std::string &message);
#else
void LogFunction(const std::string &category, Verbosity verbosity, const std::string &message) {
	auto &stream = (verbosity == Fatal || verbosity == Error) ? std::cerr : std::cout;

	StreamFormat(stream, "[%][%]: %\n", category, verbosity, message);
}
#endif

template<typename...ArgsType>
void Log(const std::string &category, Verbosity verbosity, const char* fmt, ArgsType...args) {
#if BSL_WITH_EXTERNAL_LOG_FUNCTION
	LogFunctionExternal(category, verbosity, Format(fmt, args...));
#else
	LogFunction(category, verbosity, Format(fmt, args...));
#endif
}

#define DEFINE_LOG_CATEGORY(name) \
template<typename...ArgsType> \
static void Log##name(Verbosity verbosity, const char* fmt, ArgsType...args) { \
	Log(#name, verbosity, fmt, args...); \
} \
template<typename...ArgsType> \
static void Log##name##If(bool condition, Verbosity verbosity, const char *fmt, ArgsType...args) {\
	if(condition) Log##name(verbosity, fmt, args...); \
}
