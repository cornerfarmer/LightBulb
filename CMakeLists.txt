cmake_minimum_required(VERSION 2.6.4)
project (LightBulb)

if(MSVC)
  # Force to always compile with W4
  if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
    string(REGEX REPLACE "/W[0-4]" "/W0" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
  else()
    add_definitions(/W0)
  endif()
elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  # Update if necessary
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -w")
endif()

option(EnableLightBulbApp "EnableLightBulbApp" ON)
option(EnableLightBulbExample "EnableLightBulbExample" ON)
option(EnableUnitTests "EnableUnitTests" OFF)

add_subdirectory(src/LightBulb)

if(EnableLightBulbApp)
  add_subdirectory(src/LightBulbApp)
endif()

if(EnableLightBulbApp AND EnableLightBulbExample)
  add_subdirectory(example/LightBulbExample)
endif()

if(EnableLightBulbApp AND EnableUnitTests)
  add_subdirectory(tests/UnitTests)
endif()
