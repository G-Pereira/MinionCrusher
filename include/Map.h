#pragma once
#ifndef MINIONCRUSHER_MAP_H
#define MINIONCRUSHER_MAP_H

#include <iostream>
#include <vector>
#include <list>

#include "PathTile.h"
#include "Base.h"
#include "Blueprint.h"
#include "Tower.h"
#include "Minion.h"

class Map {
public:
    /**
     * \brief
     * @param bp Blueprint file path
     */
    Map(Blueprint *blueprint);

    ~Map();

    Base base = Base(0,0,1,1,100);
    std::vector<PathTile> path;
    std::vector<Tower> towers;
	std::list<Minion> minions;

	int x_tiles;
	int y_tiles;

};

#endif //MINIONCRUSHER_MAP_H