cmake_minimum_required(VERSION 2.6.4)
project (LightBulbExample)
include(../../cmake/macros.txt)

file(GLOB_RECURSE SOURCES *.cpp *.hpp)
include_directories(.)
include_directories(../../include)
include_directories(../../extlibs/freechart/include)
include_directories(../../extlibs/eigen)
include_directories(../../extlibs/cereal/include)
include_directories(../../extlibs/viennacl)
add_definitions(-DVIENNACL_WITH_OPENCL -DVIENNACL_WITH_EIGEN)

set(wxWidgets_CONFIGURATION mswu)
find_package(wxWidgets COMPONENTS core base richtext adv html xml aui REQUIRED)
include(${wxWidgets_USE_FILE})

find_package(OpenCL REQUIRED)

add_executable(LightBulbExample ${SOURCES})
target_link_libraries(LightBulbExample ${OpenCL_LIBRARY} LightBulb LightBulbApp freechart ${wxWidgets_LIBRARIES})
use_cxx11(LightBulbExample)
set_target_properties(LightBulbExample PROPERTIES COTIRE_CXX_PREFIX_HEADER_INIT "LightBulbExamplePrec.hpp")
cotire(LightBulbExample)