#pragma once

#include <iostream>
#include <optional>

template<typename T>
struct RawSerializer {
	static_assert(!std::is_pointer_v<T>, "Can't raw-serialize pointers");

	static void ToStream(const T& object, std::ostream& stream) {
		stream.write((const char*)std::addressof(object), sizeof(object));
	}

	static std::optional<T> FromStream(std::istream& stream) {
		T object;

		if (!stream.read((char*)std::addressof(object), sizeof(object)))
			return std::nullopt;

		return { std::move(object) };
	}
};

template<typename T>
struct Serializer {
	static void ToStream(const T& object, std::ostream& stream) { 
		RawSerializer<T>::ToStream(object, stream); 
	}

	static std::optional<T> FromStream(std::istream& stream) { 
		return RawSerializer<T>::FromStream(stream);
	}
};
