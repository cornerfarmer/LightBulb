cmake_minimum_required(VERSION 2.6.4)
project (LightBulbApp)
include(../../cmake/macros.txt)

file(GLOB_RECURSE SOURCES *.cpp)
include_directories(../../include)
include_directories(../../extlibs/freechart/include)
include_directories(../../extlibs/eigen)
include_directories(../../extlibs/cereal/include)
include_directories(../../extlibs/viennacl)
add_definitions(-DVIENNACL_WITH_OPENCL -DVIENNACL_WITH_EIGEN)

add_subdirectory(../../extlibs/freechart ${CMAKE_CURRENT_BINARY_DIR}/freechart)

set(wxWidgets_CONFIGURATION mswu)
find_package(wxWidgets COMPONENTS core base richtext adv html xml REQUIRED)
include(${wxWidgets_USE_FILE})

find_package(OpenCL REQUIRED)

add_library(LightBulbApp ${SOURCES})
target_link_libraries(LightBulbApp ${OpenCL_LIBRARY} LightBulb freechart ${wxWidgets_LIBRARIES})
use_cxx11(LightBulbApp)
install(TARGETS LightBulbApp DESTINATION lib)
install(DIRECTORY ../../include/LightBulbApp DESTINATION include)