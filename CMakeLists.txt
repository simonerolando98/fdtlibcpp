cmake_minimum_required(VERSION 3.10)
project(fdtlibcpp)

set(CMAKE_CXX_STANDARD 17)

# MSVC Static Multi Threaded Debug
if (MSVC)
	add_compile_options(
		$<$<CONFIG:>:/MT>
		$<$<CONFIG:Debug>:/MTd>
		$<$<CONFIG:Release>:/MT>
	)
endif()

include_directories(src/include)

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(lib/googletest)
