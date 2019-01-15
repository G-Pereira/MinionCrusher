#pragma once
#ifndef MINIONCRUSHER_MAP_H
#define MINIONCRUSHER_MAP_H

#include <iostream>
#include <vector>
#include <list>
#include <mutex>

#include "PathTile.h"
#include "Base.h"
#include "Tower.h"
#include "Minion.h"
#include "minions/MinionMedium.h"
#include "minions/MinionRemi.h"
#include "ammoTypes/AmmoFire.h"
#include "ammoTypes/AmmoFreeze.h"

/**
 * Map holds all elements in the game
 * and can read a level blueprint file
 */
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

    /** This function adds pathTiles to the path vector in the right order */
    bool createPath(int x, int y);

    Base base = Base(0, 0, 1, 1, 100);
    std::vector <PathTile> path;                      /// Vector containing all path tiles, in order the minions should cross them
    std::vector <Tower> towers;                       /// Vector containing all towers.
    std::list <Minion> minions;                         /// List containing all minions currently in the game.
    std::vector <std::vector<int>> mapBlueprint;      /// Vector containing a blueprint of the map. Used to initialize the map.

    int x_tiles;
    int y_tiles;

    CartesianCoordinates spawnPos;                   /// Position where minions spawn. Read from the blueprintFile


    /**
     * build a tower on the specified location if  available
     * @param: coordinates the coordinates of where to build
     * @param: type of button pressed to determine which tower should be built
     * @return: true if succesful, false if not
     */
    bool addTower(CartesianCoordinates coordinates, ButtonTypes type);

private:
    /**
     * checks if a location is available for building a tower
     * @param: coordinates the coordinates of where to build
     * @return: true if available, false if not
     */
    bool towerSpotAvailable(CartesianCoordinates coordinates);

    std::vector <CartesianCoordinates> unavailable_towerspots;        /// Set containing coordinates where you CANNOT build a tower
};

#endif //MINIONCRUSHER_MAP_H