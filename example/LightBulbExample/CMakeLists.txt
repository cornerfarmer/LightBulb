cmake_minimum_required(VERSION 2.6.4)
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
set_target_properties(LightBulbExample PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)