cmake_minimum_required(VERSION 2.6.4)
project (UnitTests)

file(GLOB_RECURSE SOURCES *.cpp *.hpp)
include_directories(.)
include_directories(../../src/LightBulb)
include_directories(../../extlibs/eigen)
include_directories(../../extlibs/cereal/include)
include_directories(../../extlibs/googletest/googletest)
include_directories(../../extlibs/googletest/googlemock)
include_directories(../../extlibs/googletest/googletest/include)
include_directories(../../extlibs/googletest/googlemock/include)

set(gtest_force_shared_crt true)
add_subdirectory(../../extlibs/googletest ${CMAKE_CURRENT_BINARY_DIR}/googletest)

add_executable(UnitTests ${SOURCES})
target_link_libraries(UnitTests LightBulb gmock)
set_target_properties(UnitTests PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)
