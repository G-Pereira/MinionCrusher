#ifndef MINIONCRUSHER_MAP_H
#define MINIONCRUSHER_MAP_H
#endif //MINIONCRUSHER_MAP_H

#include <iostream>
#include <vector>

#include "PathTile.h"
#include "Base.h"
#include "Blueprint.h"

class Map {
public:
    /**
     * The object is constructed with a blueprint from a file
     * @param bp Blueprint file path
     */
    Map(Blueprint bp);

private:
    std::vector<std::vector<MapObject>> map = {};
};