#include <fstream>
#include <string>
#include "Battlefield.h"

Battlefield::Battlefield(Blueprint *blueprint) {
    try {
        std::ifstream f(blueprint->blueprintFile);

        if (!f.good()) throw std::invalid_argument("Error reading blueprint file");

		std::string line;
		for (uint8_t x = 0; std::getline(f, line); x++) {
			for (uint8_t y = 0; y < line.length(); y++) {
				int tileType = line.at(y) - '0';
				//std::cout << "at " << (int)x << ", " << (int)y << " type " << tileType << std::endl;
				switch (tileType) {
				case 0:
					break;
				case 1:
				case 2:
				case 3:
				case 4:
					this->path.emplace_back(x, y, 1, 1, MapSlots(tileType));
					break;
				case 5:
					base = Base(x, y, 1, 1, 100);
					break;
				default:
					throw std::domain_error(
						"Battlefield blueprint has invalid entry at x=" + std::to_string(x) + " and y=" +
						std::to_string(y) + " read: " + std::to_string(tileType));
				}
			}
		}
    } catch (std::exception& e){
        std::cout << e.what();
    }
}

Battlefield::~Battlefield() {
}