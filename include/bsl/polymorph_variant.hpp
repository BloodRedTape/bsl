#pragma once

#include <variant>

template<typename BaseType, typename ...SubTypes>
class PolymorphVariant {
	using VariantType = std::variant<SubTypes...>;

	VariantType m_Value;

    template<typename T>
    static constexpr bool IsValidSubtype = (std::is_same_v<std::decay_t<T>, SubTypes> || ...);

	template<typename First, typename... Rest>
	static constexpr auto GetInitializer() -> First {
		return First{};
	}
public:
	using SubtypeId = std::size_t;
public:
	PolymorphVariant():
		m_Value(GetInitializer<SubTypes...>())
	{}

	template<typename SubType, typename = std::enable_if_t<IsValidSubtype<SubType>>>
	PolymorphVariant(SubType&& value)noexcept{
		m_Value = std::move(value);
	}

	PolymorphVariant(VariantType&& value)noexcept:
		m_Value(std::move(value))
	{}

	PolymorphVariant(const VariantType& value):
		m_Value(value)
	{}
	
	PolymorphVariant(const PolymorphVariant &other):
		PolymorphVariant(other.m_Value)
	{}

	PolymorphVariant(PolymorphVariant &&other)noexcept:
		PolymorphVariant(std::move(other.m_Value))
	{}

	
	template<typename SubType, typename = std::enable_if_t<IsValidSubtype<SubType>>>
	PolymorphVariant &operator=(SubType &&value)noexcept{
		m_Value = std::move(value);
		return *this;
	}

	PolymorphVariant &operator=(VariantType&& value)noexcept{
		m_Value = std::move(value);
		return *this;
	}

	PolymorphVariant &operator=(const VariantType& value) {
		m_Value = value;
		return *this;
	}
	
	PolymorphVariant &operator=(const PolymorphVariant &other){
		m_Value = other.m_Value;
		return *this;
	}

	PolymorphVariant& operator=(PolymorphVariant&& other) noexcept{
		m_Value = std::move(other.m_Value);
		return *this;
	}

	BaseType* Ptr() {
		return const_cast<BaseType*>(((const PolymorphVariant *)this)->Ptr());
	}

	const BaseType* Ptr()const{
		const BaseType *ptr = nullptr;

		std::visit([&](const auto& value) {
			ptr = &value;
		}, m_Value);

		return ptr;
	}

	SubtypeId Id()const {
		return m_Value.index();
	}
	
	template<typename SubType, typename = std::enable_if_t<IsValidSubtype<SubType>>>
	static SubtypeId Id() {
		size_t index = 0;
		auto test = [&](bool b){
			if (!b) ++index;
			return b;
		};
		(test(std::is_same_v<SubType, SubTypes>) || ...);

		return index;
	}

	operator VariantType()const {
		return m_Value;
	}

	BaseType* operator->() { return Ptr(); }

	const BaseType* operator->()const{ return Ptr(); }

	BaseType& operator*() { return *Ptr(); }

	const BaseType& operator*()const{ return *Ptr(); }

	template<typename SubType>
	const SubType* Cast()const{
		return std::get_if<SubType>(&m_Value);
	}

	template<typename SubType>
	SubType* Cast(){
		return const_cast<BaseType*>(((const PolymorphVariant *)this)->Cast<SubType>());
	}

	template<typename SubType>
	bool Is()const {
		return Cast<SubType>();
	}

	bool Is(SubtypeId id)const {
		return Id() == id;
	}
};
