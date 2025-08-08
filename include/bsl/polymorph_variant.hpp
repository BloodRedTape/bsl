#pragma once

#include <variant>

template<typename BaseType, typename ...SubTypes>
class PolymorphVariant {
	using VariantType = std::variant<SubTypes...>;

	VariantType m_Value;
public:
	template<typename...ArgsType>
	PolymorphVariant(ArgsType&&...args):
		m_Value(std::forward<ArgsType>(args)...)
	{}

	PolymorphVariant(VariantType&& value):
		m_Value(std::move(value))
	{}

	PolymorphVariant(const VariantType& value):
		m_Value(value)
	{}
	
	PolymorphVariant(const PolymorphVariant &other):
		PolymorphVariant(other.m_Value)
	{}

	PolymorphVariant(PolymorphVariant &&other):
		PolymorphVariant(std::move(other.m_Value))
	{}

	
	PolymorphVariant &operator=(VariantType&& value) {
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

	PolymorphVariant& operator=(PolymorphVariant&& other) {
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

	BaseType* operator->() { return Ptr(); }

	const BaseType* operator->()const{ return Ptr(); }

	BaseType& operator*() { return *Ptr(); }

	const BaseType& operator*()const{ return *Ptr(); }
};
