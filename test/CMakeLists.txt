set(TEST_BIN all_tests)

set(TEST_SOURCES main.cpp array.cpp vector.cpp matrix.cpp utility.cpp forward_list.cpp linked_list.cpp stack.cpp queue.cpp string.cpp)

add_executable(${TEST_BIN} ${TEST_SOURCES})

add_test(NAME ${TEST_BIN} COMMAND ${TEST_BIN})

target_link_libraries(${TEST_BIN} PUBLIC gtest ${CMAKE_PROJECT_NAME}_lib)
