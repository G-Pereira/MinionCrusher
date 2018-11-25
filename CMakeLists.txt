cmake_minimum_required(VERSION 3.2)
project(MinionCrusher)

set(CMAKE_CXX_STANDARD 14)

# Search SDL2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

add_executable(MinionCrusher src/main.cpp)
target_link_libraries(MinionCrusher ${SDL2_LIBRARY})