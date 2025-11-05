project(bsl)

add_library(bsl 
	"./sources/file.cpp"
	"./sources/stacktrace.cpp"
)

if(BSL_WITH_STACKTRACE)
	target_compile_definitions(bsl PUBLIC BSL_WITH_STACKTRACE=1)
	if(WIN32)
		target_link_libraries(bsl PRIVATE DbgHelp)
	endif()

	if(UNIX)
		set_property(TARGET bsl PROPERTY ENABLE_EXPORTS ON)
	endif()
else()
	target_compile_definitions(bsl PUBLIC BSL_WITH_STACKTRACE=0)
endif()

if(BSL_WITH_EXTERNAL_LOG_FUNCTION)
	target_compile_definitions(bsl PUBLIC BSL_WITH_EXTERNAL_LOG_FUNCTION=1)
endif()
if(BSL_WITH_SCOPED_VERBOSITY)
	target_compile_definitions(bsl PUBLIC BSL_WITH_SCOPED_VERBOSITY=1)
endif()
target_include_directories(bsl PUBLIC "./include")
target_compile_features(bsl PRIVATE cxx_std_17)


target_precompile_headers(bsl PUBLIC 
	"./include/bsl/defer.hpp"
	"./include/bsl/enum.hpp"
	"./include/bsl/file.hpp"
	"./include/bsl/format.hpp"
	"./include/bsl/log.hpp"
	"./include/bsl/parse.hpp"
	"./include/bsl/polymorph_variant.hpp"
	"./include/bsl/serialization.hpp"
	"./include/bsl/serialization_std.hpp"
	"./include/bsl/stdlib.hpp"
)

