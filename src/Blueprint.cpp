#include <iostream>
#include <utility>
#include <fstream>
#include <array>
#include <string>
#include "Blueprint.h"

Blueprint::Blueprint(std::string blueprintFile) : blueprintFile(std::move(blueprintFile)) {
}
