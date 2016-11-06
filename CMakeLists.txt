cmake_minimum_required(VERSION 2.8.9)
project (LightBulb)

file(GLOB_RECURSE SOURCES src/LightBulb/*.cpp src/LightBulb/*.hpp)
include_directories(src/LightBulb)

include_directories(extlibs/eigen)
include_directories(extlibs/cereal/include)

add_library(LightBulb STATIC ${SOURCES})
