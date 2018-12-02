#pragma once
#ifndef MINIONCRUSHER_MAP_H
#define MINIONCRUSHER_MAP_H

#include <iostream>
#include <vector>

#include "PathTile.h"
#include "Base.h"
#include "Blueprint.h"
#include "Tower.h"

class Map {
public:
    /**
     * The object is constructed with a blueprint from a file
     * @param bp Blueprint file path
     */
    Map(Blueprint *bp);

    ~Map();

    Base *base;
    std::vector<PathTile> path;
    std::vector<Tower> towers;
};

#endif //MINIONCRUSHER_MAP_H