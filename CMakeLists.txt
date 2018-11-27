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

add_executable(MinionCrusher ${SRCS} ${HDRS})

# Search SDL2
INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)

INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES})

# Add blueprints
configure_file(configs/simple.blueprint configs/simple.blueprint COPYONLY)