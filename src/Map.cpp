#include <fstream>
#include <string>
#include <vector>
#include "Map.h"

Map::Map(std::string blueprintFile) {
	y_tiles = 0;
	x_tiles = 0;
	spawnPos = { 0 };
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
			mapBlueprint.push_back(std::vector<int>());					// Add a new row to the blueprint
            for (x_tiles = 0; x_tiles < line.length(); x_tiles++) {
                int tileType = line.at(x_tiles) - '0';
				mapBlueprint.back().push_back(tileType);				// Add a value to the right column of the blueprint
                if (tileType>=6 && tileType <=9) {
						this->path.emplace_back(x_tiles, y_tiles, 1, 1, MapSlots(tileType-5));	// Create the path tile where the minions spawn
						spawnPos = { (float)x_tiles,(float)y_tiles };
                }
            }
        }
		int dir = mapBlueprint[spawnPos.y][spawnPos.x] - 5;
		createPath(spawnPos.x - (dir == 1) + (dir == 4), spawnPos.y - (dir == 3) + (dir == 2));

    } catch (std::exception &e) {
        std::cout << e.what();
    }
}

Map::~Map() {
}

void Map::createPath(int x, int y)
{
	int dir = mapBlueprint[y][x];
	if (dir > 0 && dir < 5) {
		//std::cout << x << " " << y << " " << dir << std::endl;
		path.emplace_back(x, y, 1, 1, MapSlots(dir));
		createPath(x - (dir == 1) + (dir == 4), y - (dir == 3) + (dir == 2));
	}
	else if(dir == 5){
		base = Base(x, y, 1, 1, 100);
	}

}

std::mutex & Map::getMutex()
{
	return mutex;
}
