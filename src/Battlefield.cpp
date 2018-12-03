#include <fstream>
#include <string>
#include "Battlefield.h"

Battlefield::Battlefield(Blueprint *blueprint) {
    try {
        std::ifstream f(blueprint->blueprintFile);

        if (!f.good()) throw std::invalid_argument("Error reading blueprint file");

		std::string line;

		for (x_tiles = 0; std::getline(f, line); x_tiles++) {
			for (y_tiles = 0; y_tiles < line.length(); y_tiles++) {
				int tileType = line.at(y_tiles) - '0';
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
					this->base = new Base(x_tiles, y_tiles, 1, 1, 100);
					break;
				default:
					throw std::domain_error(
						"Battlefield blueprint has invalid entry at x=" + std::to_string(x_tiles) + " and y=" +
						std::to_string(y_tiles) + " read: " + std::to_string(tileType));
				}
			}
		}
    } catch (std::exception& e){
        std::cout << e.what();
    }
}

Battlefield::~Battlefield() {
    delete this->base;
}