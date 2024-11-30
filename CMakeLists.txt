cmake_minimum_required(VERSION 3.5.0)
project(Robhib-8-Emulator VERSION 0.1.0 LANGUAGES C CXX)

file(GLOB_RECURSE SRCS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp")

add_executable(Robhib-8-Emulator ${SRCS})
target_include_directories(Robhib-8-Emulator PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
