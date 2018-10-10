cmake_minimum_required(VERSION 3.5)
project (ProjectKeno)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

set( GCC_COMPILE_FLAGS "-Wall" )
set( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COMPILE_FLAGS}" )

include_directories( include )

add_library(KENO STATIC "src/keno.cpp")

#target_compile_features(KENO PUBLIC cxx_std_11)
set (CMAKE_CXX_STANDARD 11)

install(TARGETS KENO ARCHIVE DESTINATION ${CMAKE_SOURCE_DIR}/lib)

link_directories( ${CMAKE_SOURCE_DIR}/lib )

add_executable(keno "src/driver_keno.cpp")

target_link_libraries(keno PRIVATE KENO )

#target_compile_features(keno PUBLIC cxx_std_11)

#add_executable(run_tests "test/test_app.cpp")

#target_link_libraries(run_tests PRIVATE ${GTEST_LIBRARIES} PRIVATE BATTLE )

#target_compile_features(run_tests PUBLIC cxx_std_11)
