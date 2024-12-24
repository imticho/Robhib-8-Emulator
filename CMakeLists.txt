cmake_minimum_required(VERSION 3.5.0)
project(Robhib-8-Emulator VERSION 0.1.0 LANGUAGES C CXX)

file(GLOB_RECURSE SRCS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/monitor/*.cpp"  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/monitor/*.h")

# Enable AddressSanitizer
set(SANITIZER_FLAGS "-fsanitize=address -g -O1 -fno-omit-frame-pointer")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${SANITIZER_FLAGS}")
set(CMAKE_LINKER_FLAGS "${CMAKE_LINKER_FLAGS} ${SANITIZER_FLAGS}")


find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
add_executable(Robhib-8-Emulator ${SRCS})
target_include_directories(Robhib-8-Emulator PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src ${CMAKE_CURRENT_SOURCE_DIR}/monitor)
target_link_libraries(Robhib-8-Emulator ${SDL2_LIBRARIES})
