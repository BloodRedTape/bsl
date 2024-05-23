#pragma once

#include <string>
#include <sstream>
#include <iostream>

inline void StreamFormat(std::ostream& stream, const char * fmt) {
	stream << fmt;
}

template<typename...ArgsType, typename T>
void StreamFormat(std::ostream& stream, const char * fmt, const T& arg, const ArgsType&... args) {
	while (*fmt) {
		char front = *fmt++;

		if (front == '%') {
			stream << arg;

			return StreamFormat(stream, fmt, args...);
		}
		stream << front;
	}
}

template<typename...ArgsType>
std::string Format(const char * fmt, const ArgsType&... args) {
	std::stringstream stream;
	StreamFormat(stream, fmt, args...);
	return stream.str();
}

template<typename T>
std::string ToString(const T& value){
	return Format("%", value);
}

template<typename...ArgsType>
void Print(const char * fmt, const ArgsType&...args) {
	StreamFormat(std::cout, fmt, args...);
}

template<typename...ArgsType>
void Println(const char * fmt, const ArgsType&...args) {
	StreamFormat(std::cout, fmt, args...);
	std::cout << '\n';
}