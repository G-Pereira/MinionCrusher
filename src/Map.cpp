
#include <Map.h>

#include "Map.h"

Map::Map(Blueprint blueprint) {
    try {
        blueprint.loadBlueprint(this);
    }
    catch (std::exception const &e) {
        std::cerr << e.what();
    }
}

Map::~Map() {
    delete this->base;
}
