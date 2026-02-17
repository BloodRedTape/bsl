#pragma once

#if BSL_WITH_SCOPED_VERBOSITY
#define BSL_VERBOSITY_MODIFIER class
#else
#define BSL_VERBOSITY_MODIFIER
#endif

#ifndef BSL_WITH_EXTERNAL_LOG_FUNCTION
	#define BSL_WITH_EXTERNAL_LOG_FUNCTION 0
#endif

#ifndef BSL_WITH_TIME_LOG
	#define BSL_WITH_TIME_LOG 0
#endif

#if BSL_WITH_TIME_LOG
#include <chrono>
#endif

#include "bsl/format.hpp"

namespace Details{
#if BSL_WITH_TIME_LOG
	static auto CurrentTime() {
		auto now = std::chrono::system_clock::now();
		std::time_t nowTime = std::chrono::system_clock::to_time_t(now);
		std::tm localTime = *std::localtime(&nowTime);
    
		return Format("%:%:%", localTime.tm_hour + 1, localTime.tm_min, localTime.tm_sec);
	}
#endif
}

enum BSL_VERBOSITY_MODIFIER Verbosity {
	Verbose,
	Display,
	Info,
	Warning,
	Error,
	Fatal
};

inline std::ostream& operator<<(std::ostream& stream, Verbosity verbosity) {
	switch (verbosity)
	{
	case Verbosity::Verbose:
		stream << "Verbose";
		break;
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



#if BSL_WITH_EXTERNAL_LOG_FUNCTION
extern void LogFunctionExternal(const std::string &category, Verbosity verbosity, const std::string &message);
#else
static void LogFunction(const std::string &category, Verbosity verbosity, const std::string &message) {
	auto &stream = (verbosity == Fatal || verbosity == Error) ? std::cerr : std::cout;

	auto time_string = 
#if BSL_WITH_TIME_LOG 
	Format("[%]", Details::CurrentTime());
#else
	"";
#endif

	StreamFormat(stream, "%[%][%]: %\n", time_string, category, verbosity, message);
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
