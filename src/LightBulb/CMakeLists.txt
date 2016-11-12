cmake_minimum_required(VERSION 2.6.4)
project (LightBulb)

file(GLOB_RECURSE SOURCES *.cpp *.hpp)
include_directories(.)

include_directories(../../extlibs/eigen)
include_directories(../../extlibs/cereal/include)

add_library(LightBulb STATIC ${SOURCES})
target_compile_features(LightBulb PRIVATE cxx_range_for)
