#pragma once
#ifndef MINIONCRUSHER_MAP_H
#define MINIONCRUSHER_MAP_H

#include <iostream>
#include <vector>

#include "PathTile.h"
#include "Base.h"
#include "Blueprint.h"
#include "Tower.h"

class Battlefield {
public:
    /**
     * The object is constructed with a blueprint from a file
     * @param bp Blueprint file path
     */
    Battlefield(Blueprint *bp);

    ~Battlefield();

    Base *base;
    std::vector<PathTile> path;
    std::vector<Tower> towers;
};

#endif //MINIONCRUSHER_MAP_H