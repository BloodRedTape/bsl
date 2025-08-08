#pragma once

#include <variant>

template<typename BaseType, typename ...SubTypes>
class PolymorphVariant {
	using VariantType = std::variant<SubTypes...>;

	VariantType m_Value;
public:
	template<typename SubType>
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

	
	template<typename...ArgsType>
	PolymorphVariant &operator=(ArgsType&&...args)noexcept{
		m_Value = {std::forward<ArgsType>(args)...};
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
		m_Value = other.value;
		return *this;
	}

	PolymorphVariant& operator=(PolymorphVariant&& other) noexcept{
		m_Value = other.value;
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
};
