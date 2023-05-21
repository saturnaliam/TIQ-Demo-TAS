cmake_minimum_required(VERSION 3.17)

project(TDT)

set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/bin")

file(GLOB SOURCES
${PROJECT_SOURCE_DIR}/include/*.hpp
${PROJECT_SOURCE_DIR}/main.cpp)

add_executable(TDT ${SOURCES})
target_compile_options(TDT PRIVATE -std=c++17 -static -static-libstdc++)