cmake_minimum_required(VERSION 2.6.4)
project (LightBulb)
include(../../cmake/macros.txt)

file(GLOB_RECURSE SOURCES *.cpp)
include_directories(../../include)

include_directories(../../extlibs/eigen)
include_directories(../../extlibs/cereal/include)

add_library(LightBulb ${SOURCES})
use_cxx11(LightBulb)
install(TARGETS LightBulb DESTINATION lib)
install(DIRECTORY ../../include/LightBulb DESTINATION include)
install(DIRECTORY ../../extlibs/eigen/Eigen DESTINATION include)
install(DIRECTORY ../../extlibs/cereal/include/cereal DESTINATION include)
