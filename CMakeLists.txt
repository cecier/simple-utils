cmake_minimum_required(VERSION 3.24)
project(simpleutils VERSION 1.0)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(simpleutils simple_logger/source.cc)

set_property(TARGET simpleutils PROPERTY CXX_STANDARD 23)
set_property(TARGET simpleutils PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET simpleutils PROPERTY CXX_EXTENSIONS OFF)