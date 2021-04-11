cmake_minimum_required(VERSION 3.10)
project(ftl)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS_DEBUG "-Wall -O0 -g -fsanitize=address")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

# MSVC Static Multi Threaded Debug
if (MSVC)
	add_compile_options(
		$<$<CONFIG:>:/MT>
		$<$<CONFIG:Debug>:/MTd>
		$<$<CONFIG:Release>:/MT>
	)
	set(CMAKE_CXX_FLAGS_DEBUG "/Wall /Od")
	set(CMAKE_CXX_FLAGS_RELEASE "/02")
endif()

include_directories(src/include)

add_subdirectory(test)
add_subdirectory(src)
add_subdirectory(examples)
add_subdirectory(lib/googletest)
