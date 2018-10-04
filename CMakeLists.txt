cmake_minimum_required(VERSION 3.10)
project(lab1final)

set(CMAKE_CXX_STANDARD 11)


set(CMAKE_CXX_STANDARD 11)
add_subdirectory(lib/googletest/googletest)
include_directories(lib/googletest/googletest/include)
include_directories(lib/googletest/googlemock/include)

set(SOURCE_FILES     Test/tbitfield.h  Test/tbitfield.cpp   Test/tset.cpp Test/tset.h test_tset.cpp test_tbitfield.cpp test_main.cpp test_tbitfield.cpp  Test/tbitfield.cpp Test/tbitfield.h Test/tset.cpp Test/tset.h)
add_executable(lab1final  ${SOURCE_FILES}  Test/tbitfield.h  Test/tbitfield.cpp   Test/tset.cpp Test/tset.h Test/tbitfield.cpp Test/tbitfield.h Test/tset.cpp Test/tset.h)
target_link_libraries(lab1final gtest gtest_main)