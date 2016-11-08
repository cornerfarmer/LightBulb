cmake_minimum_required(VERSION 2.8.9)
project (LightBulbExample)

file(GLOB_RECURSE SOURCES *.cpp *.hpp)
include_directories(.)
include_directories(../../src/LightBulb)
include_directories(../../src/LightBulbApp)
include_directories(../../extlibs/freechart/include)
include_directories(../../extlibs/eigen)
include_directories(../../extlibs/cereal/include)

set(wxWidgets_CONFIGURATION mswu)
find_package(wxWidgets COMPONENTS core base richtext adv html xml REQUIRED)
include(${wxWidgets_USE_FILE})

add_executable(LightBulbExample ${SOURCES})
target_link_libraries(LightBulbExample LightBulb LightBulbApp freechart ${wxWidgets_LIBRARIES})
target_compile_features(LightBulbExample PRIVATE cxx_range_for)
