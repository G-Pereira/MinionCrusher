/**
 * This class holds all elements in the game, and can read a level blueprint file
 */
#pragma warning( push )
#include <fstream>
#include <vector>
#pragma warning( pop )

#include "Map.h"

Map::Map(std::string blueprintFile) {
    y_tiles = 0;
    x_tiles = 0;
    spawnPos = {0, 0};
    try {
        std::ifstream f(blueprintFile);
        /**
        * The blueprintFile contains information in ASCII showing the map layout. The following values are used:
        *	0: empty map
        *	1: path left
        *	2: path downwards
        *	3: path upwards
        *	4: path right
        *	5: base
        *	6: spawn + path left
        *	7: spawn + path downwards
        *	8: spawn + path upwards
        *	9: spawn + path right
        */

        if (!f.good()) throw std::invalid_argument("Error reading blueprint file");

        std::string line;

        for (y_tiles = 0; std::getline(f, line); y_tiles++) {
            mapBlueprint.push_back(std::vector<int>());                    // Add a new row to the blueprint
            for (x_tiles = 0; x_tiles < line.length(); x_tiles++) {
                int tileType = line.at(x_tiles) - '0';
                mapBlueprint.back().push_back(
                        tileType);                // Add a value to the right column of the blueprint
                if (tileType >= 6 && tileType <= 9) {
                    this->path.emplace_back(x_tiles, y_tiles, 1, 1,
                                            MapSlots(tileType - 5));    // Create the path tile where the minions spawn
                    spawnPos = {(float) x_tiles, (float) y_tiles};
					unavailable_towerspots.push_back(spawnPos);
                }
            }
        }
        int dir = mapBlueprint[(int) spawnPos.y][(int) spawnPos.x] - 5;
        createPath((int) spawnPos.x - (int) (dir == 1) + (int) (dir == 4),
                   (int) spawnPos.y - (int) (dir == 3) + (int) (dir == 2));

    } catch (std::exception &e) {
        std::cout << e.what();
    }
}

Map::~Map() {
}

void Map::createPath(int x, int y) {
    int dir = mapBlueprint[y][x];
    if (dir > 0 && dir < 5) {
        path.emplace_back(x, y, 1, 1, MapSlots(dir));
		unavailable_towerspots.push_back(CartesianCoordinates{ (float)x,(float)y });
        createPath(x - (dir == 1) + (dir == 4), y - (dir == 3) + (dir == 2));
    } else if (dir == 5) {
        base = Base((float) x, (float) y, 1., 1., 100.);
		unavailable_towerspots.push_back(CartesianCoordinates{ (float)x,(float)y });
    }

}

bool Map::towerSpotAvailable(CartesianCoordinates coordinates)
{
	std::cout << coordinates.x << " " << coordinates.y << std::endl;
	std::cout << x_tiles << " " << y_tiles << std::endl;
	if (coordinates.x != floor(coordinates.x)) {
		std::cout << "x coordinate is not a whole number";
		return false;
	}
	if (coordinates.y != floor(coordinates.y)) {
		std::cout << "y coordinate is not a whole number";
		return false;
	}
	if (coordinates.x >= x_tiles || 0 > coordinates.x) {
		std::cout << "x coordinate is outside of map";
		return false;
	}
	if(coordinates.y >= y_tiles || 0 > coordinates.y) {
		std::cout << "y coordinate is outside of map";
		return false;
	}
	if (std::find(unavailable_towerspots.begin(), unavailable_towerspots.end(), coordinates) != unavailable_towerspots.end()) {
		std::cout << "Something is already in this spot";
		return false;
	}

	return true;
}
