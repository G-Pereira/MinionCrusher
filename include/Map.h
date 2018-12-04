/**
 * Author: Gonçalo Camelo Neves Pereira
 * Created on: 29-11-18
 * Last Modified: 03-11-18
 */

#pragma once
#ifndef MINIONCRUSHER_MAP_H
#define MINIONCRUSHER_MAP_H

#include <iostream>
#include <vector>
#include <list>

#include "PathTile.h"
#include "Base.h"
#include "Tower.h"
#include "Minion.h"

class Map {
public:
    /**
     * \brief The Map of the game that holds all of its entities
     *
     * A new Map is always generated by a blueprint present on the system and from then on holds every entity
     * that is displayed as a map to the player.
     * @param blueprint Blueprint file path
     */
    Map(std::string blueprintFile = "resources/blueprints/simple.blueprint");

    ~Map();

    Base base = Base(0,0,1,1,100);
    std::vector<PathTile> path;
    std::vector<Tower> towers;
	std::list<Minion> minions;

    uint8_t x_tiles;
    uint8_t y_tiles;

};

#endif //MINIONCRUSHER_MAP_H