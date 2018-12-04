:: This file should be placed at the top level of your project
:: i.e. it should be in the same folder as the "src" folder (containing .cpp files)
:: and the "include" folder (containing .h files).

:: Provided example adapted (not written by us)

@echo Compiling your program...

@echo off
:: specify location where SDL2 is installed
set SDL2dir="c:\SDL2"
set SDL2libdir="c:\SDL2\lib\x64"

setlocal ENABLEDELAYEDEXPANSION
set cppfiles=
for /f %%i in ('dir src\*.cpp /b /a-d') do (
    set cppfiles=!cppfiles! "src\%%i"
)
echo on

mkdir obj


:: `cl` is the MSVC compiler

cl %cppfiles% /W3 /EHsc /std:c++latest /I include /I %SDL2dir%\include /Fo.\obj\ /link /SUBSYSTEM:CONSOLE %SDL2libdir%\SDL2.lib %SDL2libdir%\SDL2main.lib /out:MinionCrusher.exe
if %errorlevel% neq 0 exit /b %errorlevel%

@echo.
@echo Running your program...
MinionCrusher.exe
