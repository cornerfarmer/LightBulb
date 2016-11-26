cmake_minimum_required(VERSION 2.6.4)
project (LightBulbExample)
include(../../cmake/macros.txt)

file(GLOB_RECURSE SOURCES *.cpp *.hpp)
include_directories(.)
include_directories(../../src/LightBulb)
include_directories(../../src/LightBulbApp)
include_directories(../../extlibs/freechart/include)
include_directories(../../extlibs/eigen)
include_directories(../../extlibs/cereal/include)

set(wxWidgets_CONFIGURATION mswu)
find_package(wxWidgets COMPONENTS core base richtext adv html xml aui REQUIRED)
include(${wxWidgets_USE_FILE})

add_executable(LightBulbExample ${SOURCES})
target_link_libraries(LightBulbExample LightBulb LightBulbApp freechart ${wxWidgets_LIBRARIES})
use_cxx11()
