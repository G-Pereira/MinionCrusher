# MinionCrusher - The Game
The sections below explain how to run the code, and show the directory structure.

## Dependencies
### Linux
In order to compile and run the application, the following packages are required:

- SDL2
- SDL2-Image
- SDL2-TTF (sometimes already in SDL2)
- gcc/g++
- cmake

If one is using Ubuntu, these can all be installed with:

```
sudo apt install libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev gcc g++ cmake
```

## Compilation


In order to make the code easy to compile the scripts from the pacman provided example were adapted to our code. They can be found and executed in the project’s directory.

As an alternative a CMake makefile was designed in order to compile the code in two easy steps in every platform that has GCC (g++ or clang) and SDL2 installed as well as PkgConfig. From the root directory execute:
cmake .
cmake . --build
And then a executable file is generated that can be run and the game can be played right away.

