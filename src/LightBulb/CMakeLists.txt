cmake_minimum_required(VERSION 2.8.9)
project (LightBulb)

file(GLOB_RECURSE SOURCES *.cpp *.hpp)
include_directories(.)

include_directories(../../extlibs/eigen)
include_directories(../../extlibs/cereal/include)

add_library(LightBulb STATIC ${SOURCES})
