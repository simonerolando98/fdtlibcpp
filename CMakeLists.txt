cmake_minimum_required(VERSION 3.10)
project(fdtlibcpp)

set(CMAKE_CXX_STANDARD 20)

include_directories(src/include)

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(lib/googletest)
