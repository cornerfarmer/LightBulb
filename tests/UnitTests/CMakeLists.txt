cmake_minimum_required(VERSION 2.6.4)
project (UnitTests)
include(../../cmake/macros.txt)

file(GLOB_RECURSE SOURCES *.cpp *.hpp)
include_directories(.)
include_directories(../../include)
include_directories(../../extlibs/eigen)
include_directories(../../extlibs/cereal/include)
include_directories(../../extlibs/viennacl)
include_directories(../../extlibs/googletest/googletest)
include_directories(../../extlibs/googletest/googlemock)
include_directories(../../extlibs/googletest/googletest/include)
include_directories(../../extlibs/googletest/googlemock/include)
add_definitions(-DVIENNACL_WITH_OPENCL -DVIENNACL_WITH_EIGEN)

set(gtest_force_shared_crt true)
add_subdirectory(../../extlibs/googletest ${CMAKE_CURRENT_BINARY_DIR}/googletest)

find_package(OpenCL REQUIRED)

add_executable(UnitTests ${SOURCES})
target_link_libraries(UnitTests ${OpenCL_LIBRARY} LightBulb gmock)
use_cxx11(UnitTests)
