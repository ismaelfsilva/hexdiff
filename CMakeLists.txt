cmake_minimum_required(VERSION 3.16)
project(hexdiff CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(hexdiff_lib src/hexdiff.cpp)
target_include_directories(hexdiff_lib PUBLIC include)

add_executable(hexdiff src/main.cpp)
target_link_libraries(hexdiff PRIVATE hexdiff_lib)

enable_testing()
if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_hexdiff.cpp)
    add_executable(test_hexdiff tests/test_hexdiff.cpp)
    target_link_libraries(test_hexdiff PRIVATE hexdiff_lib)
    add_test(NAME test_hexdiff COMMAND test_hexdiff)
endif()
