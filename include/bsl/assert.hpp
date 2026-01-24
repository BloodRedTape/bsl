#pragma once

#include <bsl/log.hpp>
#include <bsl/stacktrace.hpp>

DEFINE_LOG_CATEGORY(Assert)

#define ensure(expr) \
[expr_result = (expr)]() { \
	LogAssertIf(!expr_result, Error, "Expression '%' evaluated to false, can't proceed. Stacktrace: \n%", #expr, Stacktrace()); \
	return expr_result; \
}()
