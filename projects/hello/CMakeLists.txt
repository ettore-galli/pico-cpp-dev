cmake_minimum_required(VERSION 3.13)
project(HelloWorld VERSION 1.0.0.0 LANGUAGES C CXX)

add_executable(HelloWorld hello.cpp)

set(CMAKE_CXX_STANDARD 10)
set(CMAKE_CXX_STANDARD_REQUIRED True)


set(TITLE_STRING "Square Root Calculator (SRC)")
configure_file(variables.h.in variables.h @ONLY)

target_include_directories(HelloWorld PUBLIC "${PROJECT_BINARY_DIR}") 
