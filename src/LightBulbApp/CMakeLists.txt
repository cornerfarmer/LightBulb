cmake_minimum_required(VERSION 2.6.4)
project (LightBulbApp)

file(GLOB_RECURSE SOURCES *.cpp *.hpp)
include_directories(.)
include_directories(../LightBulb)
include_directories(../../extlibs/freechart/include)
include_directories(../../extlibs/eigen)
include_directories(../../extlibs/cereal/include)

add_subdirectory(../../extlibs/freechart ${CMAKE_CURRENT_BINARY_DIR}/freechart)

set(wxWidgets_CONFIGURATION mswu)
find_package(wxWidgets COMPONENTS core base richtext adv html xml REQUIRED)
include(${wxWidgets_USE_FILE})

add_library(LightBulbApp STATIC ${SOURCES})
target_link_libraries(LightBulbApp LightBulb freechart ${wxWidgets_LIBRARIES})
target_compile_features(LightBulbApp PRIVATE cxx_range_for)
