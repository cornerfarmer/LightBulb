cmake_minimum_required(VERSION 2.6.4)
project (LightBulbApp)
include(../../cmake/macros.txt)

file(GLOB_RECURSE SOURCES *.cpp)
include_directories(../../include)
include_directories(../../extlibs/freechart/include)
include_directories(../../extlibs/eigen)
include_directories(../../extlibs/cereal/include)

add_subdirectory(../../extlibs/freechart ${CMAKE_CURRENT_BINARY_DIR}/freechart)

set(wxWidgets_CONFIGURATION mswu)
find_package(wxWidgets COMPONENTS core base richtext adv html xml REQUIRED)
include(${wxWidgets_USE_FILE})

add_library(LightBulbApp ${SOURCES})
target_link_libraries(LightBulbApp LightBulb freechart ${wxWidgets_LIBRARIES})
use_cxx11(LightBulbApp)
install(TARGETS LightBulbApp DESTINATION lib)
install(DIRECTORY ../../include/LightBulbApp DESTINATION include)