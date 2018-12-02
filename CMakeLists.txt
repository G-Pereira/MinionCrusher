cmake_minimum_required(VERSION 3.8)
project(MinionCrusher)

# Set C++ version
set(CMAKE_CXX_STANDARD 14)

#Turn on warnings
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror")

#Set your directories.  The dot representes the root application folder.
#Thus my the path to my domain folder:
set(INCLUDE_DIR ./include)
set(SOURCE_DIR ./src)

# Include directories
include_directories(${INCLUDE_DIR})
include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${SDL2IMAGE_INCLUDE_DIRS})

file(GLOB_RECURSE SOURCE_FILES ${HEADER_FILES}/*.h)
file(GLOB_RECURSE SOURCE_FILES ${SOURCE_DIR}/*.cpp)

# Search SDL2
include(FindPkgConfig)

pkg_search_module(SDL2 REQUIRED sdl2)
pkg_search_module(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)

configure_file(resources/blueprints/simple.blueprint resources/blueprints/simple.blueprint COPYONLY)
configure_file(resources/blueprints/simple.blueprint resources/blueprints/simple.blueprint COPYONLY)

add_executable(MinionCrusher ${HEADER_FILES} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} SDL2main SDL2)