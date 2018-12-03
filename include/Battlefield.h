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

class Battlefield {
public:
    /**
     * The object is constructed with a blueprint from a file
     * @param bp Blueprint file path
     */
    Battlefield(Blueprint *blueprint);

    ~Battlefield();

    Base base = Base(0,0,1,1,100);
    std::vector<PathTile> path;
    std::vector<Tower> towers;
	std::list<Minion> minions;
	
};

#endif //MINIONCRUSHER_MAP_H