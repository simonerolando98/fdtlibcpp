cmake_minimum_required(VERSION 3.10)
project(fdtlibcpp)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS_DEBUG "-Wall -O0 -g -march=i386")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

set(CMAKE_BUILD_TYPE Debug)

# MSVC Static Multi Threaded Debug
if (MSVC)
	add_compile_options(
		$<$<CONFIG:>:/MT>
		$<$<CONFIG:Debug>:/MTd>
		$<$<CONFIG:Release>:/MT>
	)
endif()

include_directories(src/include)

add_subdirectory(test)
add_subdirectory(lib/googletest)
