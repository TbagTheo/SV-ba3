cmake_minimum_required (VERSION 2.6)
project (Neuron)

#find_package(GTest REQUIRED)
#include_directories(${GTEST_INCLUDE_DIRS})

set(CMAKE_CXX_FLAGS " -W -Wall -pedantic -std=c++11")
add_executable (neuron main.cpp Neuron.cpp Simulation.cpp)
#add_executable(runTests tests.cpp)
#target_link_libraries(runTargets ${GTEST_LIBRARIES} pthread)
