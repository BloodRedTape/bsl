#pragma once

#include <utility>
#include <functional>

#ifndef CAT
#ifndef CAT_IMPL
#define CAT_IMPL(a, b) a##b
#define CAT(a, b) CAT_IMPL(a, b)
#endif
#endif

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

#define BSL_DEFER DeferType CAT(__defer_, __LINE__) = PredicateInjector() << [&]
