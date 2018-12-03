#include <fstream>
#include <string>
#include "Map.h"

Map::Map(Blueprint *blueprint) {
    try {
        std::ifstream f(blueprint->blueprintFile);

        if (!f.good()) throw std::invalid_argument("Error reading blueprint file");

		std::string line;

		for (y_tiles = 0; std::getline(f, line); y_tiles++) {
			for (x_tiles = 0; x_tiles < line.length(); x_tiles++) {
				int tileType = line.at(x_tiles) - '0';
				//std::cout << "at " << (int)x << ", " << (int)y << " type " << tileType << std::endl;
				switch (tileType) {
				case 0:
					break;
				case 1:
				case 2:
				case 3:
				case 4:
					this->path.emplace_back(x_tiles, y_tiles, 1, 1, MapSlots(tileType));
					break;
				case 5:
					this->base = Base(x_tiles, y_tiles, 1, 1, 100);
					break;
				default:
					throw std::domain_error(
						"Map blueprint has invalid entry at x=" + std::to_string(x_tiles) + " and y=" +
						std::to_string(y_tiles) + " read: " + std::to_string(tileType));
				}
			}
		}
    } catch (std::exception& e){
        std::cout << e.what();
    }
}

Map::~Map() {
}