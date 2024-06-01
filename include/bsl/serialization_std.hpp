#pragma once

#include "bsl/serialization.hpp"
#include <string>
#include <vector>
#include <unordered_map>

template<>
struct Serializer<std::string>{
	static void ToStream(const std::string& string, std::ostream& stream) {
		Serializer<std::size_t>::ToStream(string.size(), stream);
		stream.write(string.data(), string.size());
	}

	static std::optional<std::string> FromStream(std::istream& stream) {
		auto size = Serializer<std::size_t>::FromStream(stream);

		if(!size.has_value())
			return std::nullopt;

		std::string string(size.value(), '\0');

		if(!stream.read(string.data(), string.size()))
			return std::nullopt;

		return {std::move(string)};
	}
};

template<typename T>
struct Serializer<std::vector<T>>{
	static void ToStream(const std::vector<T>& vector, std::ostream& stream) {
		Serializer<std::size_t>::ToStream(vector.size(), stream);

		for (const auto &e : vector)
			Serializer<T>::ToStream(e, stream);
	}

	static std::optional<std::vector<T>> FromStream(std::istream& stream) {
		auto size = Serializer<std::size_t>::FromStream(stream);

		if(!size.has_value())
			return std::nullopt;

		std::vector<T> vector;
		
		for(int i = 0; i<size.value(); i++) {
			auto e = Serializer<T>::FromStream(stream);

			if(!e.has_value())
				return std::nullopt;

			vector.emplace_back(std::move(e.value()));
		}

		return {std::move(vector)};
	}
};

template<typename F, typename S>
struct Serializer<std::pair<F, S>>{
	static void ToStream(const std::pair<F, S>& pair, std::ostream& stream) {
		Serializer<F>::ToStream(pair.first, stream);
		Serializer<S>::ToStream(pair.second, stream);
	}

	static std::optional<std::pair<F, S>> FromStream(std::istream& stream) {
		auto first  = Serializer<F>::FromStream(stream);
		auto second = Serializer<S>::FromStream(stream);
		
		if(!first.has_value() || !second.has_value())
			return std::nullopt;

		return {{std::move(first.value()), std::move(second.value())}};
	}
};

template<typename KeyType, typename ValueType>
struct Serializer<std::unordered_map<KeyType, ValueType>>{
	static void ToStream(const std::unordered_map<KeyType, ValueType>& map, std::ostream& stream) {
		Serializer<std::size_t>::ToStream(map.size(), stream);

		for (const auto& pair : map)
			Serializer<std::pair<KeyType, ValueType>>::ToStream(pair, stream);
	}

	static std::optional<std::unordered_map<KeyType, ValueType>> FromStream(std::istream& stream) {
		auto size = Serializer<std::size_t>::FromStream(stream);

		if(!size.has_value())
			return std::nullopt;
	
		std::unordered_map<KeyType, ValueType> map;

		for(int i = 0; i<size.value(); i++) {
			auto pair = Serializer<std::pair<KeyType, ValueType>>::FromStream(stream);

			if(!pair.has_value())
				return std::nullopt;
			
			map.emplace(std::move(pair.value()));
		}
		
		return {std::move(map)};
	}
};
