#include <iostream>
#include <utility>
#include <fstream>
#include <array>
#include <string>
#include "Blueprint.h"

Blueprint::Blueprint(std::string configFile) : configFile(std::move(configFile)) {
}

void Blueprint::loadBlueprint(Battlefield *map) {
    std::ifstream f(configFile);

    if (!f.good()) throw std::invalid_argument("Error reading blueprint file");
	
    std::string line;
    for (uint8_t x = 0; std::getline(f, line); x++) {
        for (uint8_t y = 0; y < line.length(); y++) {
            int tileType = std::stoi(line);
            switch(tileType){
                case 0:
                case 1:
                case 2:
                case 3:
                case 4:
                    map->path.emplace_back(x, y, 1, 1, MapSlots(tileType));
                    break;
                case 5:
                    map->base = new Base(x, y, 1, 1, 100);
                    break;
                default:
                    throw std::domain_error(
                            "Battlefield blueprint has invalid entry at x=" + std::to_string(x) + " and y=" + std::to_string(y));
            }
        }
    }
}
