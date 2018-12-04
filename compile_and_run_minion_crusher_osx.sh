# This file should be placed at the top level of your project
# i.e. it should be in the same folder as the "src" folder (containing .cpp files)
# and the "include" folder (containing .h files)

# Provided example adapted (not written by us)

# Stop upon error
set -e

CXX="${CXX:=clang++}"

$CXX src/*.cpp -Wall -Wextra -std=c++14 -I include -o MinionCrusher -framework SDL2 -framework Cocoa -I /Library/Frameworks -I /Library/Frameworks/SDL2.framework/Headers

./MinionCrusher
