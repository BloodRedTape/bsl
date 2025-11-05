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
