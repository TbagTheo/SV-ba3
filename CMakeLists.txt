cmake_minimum_required (VERSION 2.6)
project (Neuron)

#find_package(GTest REQUIRED)
enable_testing()
add_subdirectory(googletest)
include_directories(${GTEST_INCLUDE_DIRS}/ ${gtest_SOURCE_DIR})

set(CMAKE_CXX_FLAGS " -W -Wall -pedantic -std=c++11")
add_executable (neuron main.cpp Neuron.cpp Simulation.cpp)

add_executable(runTests tests.cpp  Simulation.cpp Neuron.cpp)
target_link_libraries(runTests gtest gtest_main)
add_test(runTests runTests)
#target_link_libraries(runTests ${GTEST_LIBRARIES} pthread)
