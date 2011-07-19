cmake_minimum_required(VERSION 2.6)
   
set(LP_SOURCE_DIR "src")
SET(CMAKE_CXX_COMPILER "clang++")

project(lp)
set(EXECUTABLE_OUTPUT_PATH bin/${CMAKE_BUILD_TYPE})

find_package(BISON)
find_package(FLEX)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -Wall -Wextra -pedantic -ansi -Wno-unused-parameter -Wno-unused-function")
message( "CXX Flags: ${CMAKE_CXX_FLAGS}" )

bison_target(Parser ${LP_SOURCE_DIR}/lp.y ${LP_SOURCE_DIR}/parser.cc)
flex_target(Scanner ${LP_SOURCE_DIR}/lp.l ${LP_SOURCE_DIR}/lexer.cc)
add_flex_bison_dependency(Scanner Parser)

file (
  GLOB
  sources
  src/*
)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_executable(
  lp
  ${sources}
  ${BISON_MyParser_OUTPUTS}
  ${FLEX_MyScanner_OUTPUTS}
)

