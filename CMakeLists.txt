project(bsl)

add_library(bsl 
	"./sources/file.cpp"
)
target_include_directories(bsl PUBLIC "./include")