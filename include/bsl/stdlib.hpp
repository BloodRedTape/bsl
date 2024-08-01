#pragma once

#include <cstdlib>
#include <optional>

template<typename RetType, typename ...ArgsType>
std::optional<RetType> ErrnoSafeCall(RetType (*function)(ArgsType...), ArgsType...args) {
	errno = 0;

	RetType result = (*function)(args...);

	if(errno)
		return std::nullopt;

	return std::make_optional(result);
}