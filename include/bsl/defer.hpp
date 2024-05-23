#pragma once

#include <utility>
#include <functional>

#define CAT_IMPL(a, b) a##b
#define CAT(a, b) CAT_IMPL(a, b)

struct PredicateInjector {
	std::function<void(void)> Predicate;

	template<typename PredicateType>
	PredicateInjector& operator<<(PredicateType &&predicate) {
		Predicate = predicate;
		return *this;
	}
};

class DeferType{
	std::function<void(void)> m_Predicate;
public:
	DeferType() = default;

	DeferType(const PredicateInjector &other)noexcept {
		m_Predicate = other.Predicate;
	}

	~DeferType() {
		if(m_Predicate)
			m_Predicate();
	}
	
};

#define defer DeferType CAT(__defer_, __LINE__) = PredicateInjector() << [&]
