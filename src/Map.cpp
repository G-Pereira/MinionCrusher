#include "Map.h"

Map::Map(Blueprint blueprint) {
    try {
        blueprint.loadBlueprint(map);
    }
    catch (std::exception const &e) {
        std::cerr << e.what();
    }
}
