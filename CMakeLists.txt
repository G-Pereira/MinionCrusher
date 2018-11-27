cmake_minimum_required(VERSION 3.2)
project(MinionCrusher)

set(CMAKE_CXX_STANDARD 14)

#Set your directories.  The dot representes the root application folder.
#Thus my the path to my domain folder:
set(INCLUDE_DIR ./include)
set(SOURCE_DIR ./src)

# Include directories
include_directories(${INCLUDE_DIR})

file(GLOB_RECURSE SRCS ${SOURCE_DIR}/*.cpp)
file(GLOB_RECURSE HDRS ${INCLUDE_DIR}*.h)

# Search SDL2
find_package(SDL2 REQUIRED)
include_directories(${SDL_INCLUDE_DIRS}/SDL2)

configure_file(configs/simple.blueprint configs/simple.blueprint COPYONLY)

add_executable(MinionCrusher ${SRCS} ${HDRS})

target_link_libraries(MinionCrusher SDL2)