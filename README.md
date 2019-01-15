# MinionCrusher - Instructions Manual
The sections below explain how to run the code, and show the directory structure.

## Dependencies
### Linux
In order to compile and run the application, the following packages are required:

- SDL2
- SDL2-Image
- SDL2-TTF (sometimes already in SDL2)
- gcc/g++
- cmake
- pkgconfig

If one is using Ubuntu, these can all be installed with:

```
sudo apt install libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev gcc g++ cmake pkgconfig
```

## Compilation
In all cases, CMake can be used to build the application. Assuming you are in the root of this repository, the program can 
be compiled with:
```
cmake .
cmake --build .
```
The second command will build the actual program, resulting in a ```CMakeFiles``` directory full with object files. 
The actual program is compiled as ```MinionCrusher``` and is placed in the root directory.

## Running
### Linux
After compilation with CMake, the executable is found in the root directory. It is executed with:
```
./MinionCrusher
```
