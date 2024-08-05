project(bsl)

add_library(bsl 
	"./sources/file.cpp"
)


if(BSL_WITH_EXTERNAL_LOG_FUNCTION)
	target_compile_definitions(bsl PUBLIC BSL_WITH_EXTERNAL_LOG_FUNCTION=1)
endif()
if(BSL_WITH_SCOPED_VERBOSITY)
	target_compile_definitions(bsl PUBLIC BSL_WITH_SCOPED_VERBOSITY=1)
endif()
target_include_directories(bsl PUBLIC "./include")