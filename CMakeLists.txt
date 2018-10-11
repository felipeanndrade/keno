cmake_minimum_required(VERSION 3.5)
project (ProjectKeno)

set( GCC_COMPILE_FLAGS "-Wall" )
set( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COMPILE_FLAGS}" )

include_directories( include )

set(CMAKE_CXX_STANDARD 11)

add_executable(keno "src/driver_keno.cpp" "src/keno.cpp")