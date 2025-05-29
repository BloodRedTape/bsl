#pragma once

#include <bsl/macro.hpp>
#include <string_view>
#include <optional>

#define BSL_ENUM_MAKE_MEMBER_NAME(name) #name ,
#define BSL_ENUM_GENERATE_MEMBER_DECLARATION(name) static const ThisEnumType name;
#define BSL_ENUM_GENERATE_MEMBER_DEFINITION(name, index, EnumTypeName) inline const EnumTypeName BSL_EXPAND(EnumTypeName) :: BSL_EXPAND(name) = index;

#define BSL_ENUM(EnumTypeName, ...) \
class EnumTypeName { \
private: \
    std::int32_t m_Value; \
private: \
    constexpr EnumTypeName(std::int32_t value): \
        m_Value(value) \
    {} \
	using ThisEnumType = EnumTypeName; \
public: \
	BSL_FOR_EACH(BSL_ENUM_GENERATE_MEMBER_DECLARATION, __VA_ARGS__) \
\
	static const auto &Names() { \
		static std::string_view s_Names[] = { \
			BSL_FOR_EACH(BSL_ENUM_MAKE_MEMBER_NAME, __VA_ARGS__) \
		}; \
\
		return s_Names; \
	} \
\
	static const auto &Values() { \
		static EnumTypeName s_Values[] = { \
			__VA_ARGS__ \
		}; \
		return s_Values; \
	} \
	std::int32_t AsInt()const { \
		return m_Value; \
	} \
\
	std::string_view Name()const { \
		return Names()[m_Value]; \
	} \
\
	bool operator==(const EnumTypeName &other)const{ \
		return m_Value == other.m_Value; \
	} \
\
	bool operator!=(const EnumTypeName &other)const{ \
		return m_Value != other.m_Value; \
	} \
\
	static std::optional<EnumTypeName> FromString(std::string_view string) {\
		for(std::int32_t i = 0; i<std::size(Names()); i++){ \
			if(Names()[i] == string) \
				return EnumTypeName(i); \
		} \
		return std::nullopt; \
\
	}\
\
}; \
BSL_FOR_EACH_INDEXED_PARAM(BSL_ENUM_GENERATE_MEMBER_DEFINITION, EnumTypeName, __VA_ARGS__)


