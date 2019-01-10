cmake_minimum_required(VERSION 3.8)
project(MinionCrusher)

# Set C++ version
set(CMAKE_CXX_STANDARD 14)

#Turn on warnings
set(CMAKE_CXX_FLAGS "-g -O0 -Wall -Wextra")

#Set your directories.  The dot representes the root application folder.
#Thus my the path to my domain folder:
set(INCLUDE_DIR include)
set(SOURCE_DIR src)
set(RESOURCES_DIR resources)

# Include directories
include_directories(${INCLUDE_DIR})
include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${SDL2IMAGE_INCLUDE_DIRS})

# Search SDL2
include(FindPkgConfig)

pkg_search_module(SDL2 REQUIRED sdl2)
pkg_search_module(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
pkg_search_module(SDL2TTF REQUIRED SDL2_ttf>=2.0.0)

configure_file(resources/blueprints/simple.blueprint resources/blueprints/simple.blueprint COPYONLY)
configure_file(resources/blueprints/simple.blueprint resources/blueprints/simple.blueprint COPYONLY)

file(GLOB_RECURSE HEADER_FILES ${INCLUDE_DIR}/*.h)
file(GLOB_RECURSE SOURCE_FILES ${SOURCE_DIR}/*.cpp)
file(GLOB RESOURCES_FILES ${RESOURCES_DIR}/*)
file(INSTALL ${RESOURCES_FILES} DESTINATION resources)

add_executable(MinionCrusher ${HEADER_FILES} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL2TTF_LIBRARIES})