#include <iostream>
#include <utility>
#include <fstream>
#include <array>
#include "Blueprint.h"

Blueprint::Blueprint(std::string configFile) : configFile(std::move(configFile)) {
}

void Blueprint::loadBlueprint(std::vector<std::vector<MapObject>> map) {
    std::ifstream f(configFile);

    if (!f.good()) throw std::invalid_argument("Error reading blueprint file");

    std::string line;
    for (uint8_t x = 0; std::getline(f, line); x++) {
        std::vector<MapObject> mapline = {};
        for (uint8_t y = 0; y < line.length(); y++) {
            int tileType = std::stoi(line);
            if (tileType < 0 || tileType > 6)
                throw std::domain_error(
                        "Map blueprint has invalid entry at x=" + std::to_string(x) + " and y=" + std::to_string(y));
            mapline.push_back(PathTile(x, y, 1, 1, MapSlots(tileType)));
        }
        map.push_back(mapline);
    }
}
