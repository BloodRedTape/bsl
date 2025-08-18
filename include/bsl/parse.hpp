#pragma once

#include <string>
#include <optional>
#include <sstream>

template<typename T>
std::optional<T> FromString(const std::string& string) {
    std::stringstream sstream(string);
    T result = {};
    sstream >> result;

    if (sstream.fail()) {
        return std::nullopt;
    }

    std::string remainder;
    sstream >> remainder;
    if (!remainder.empty()) {
        return std::nullopt;
    }
    
    return result;
}