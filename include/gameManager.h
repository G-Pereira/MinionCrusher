#ifndef MINIONCRUSHER_GAMEMANAGER_H
#define MINIONCRUSHER_GAMEMANAGER_H

#include "Map.h"

/** Needs to be called every tick to update the game. Will update towers, minions, etc. */
class GameManager {
public:
    GameManager();

	int money;
    Map *map;        /// Pointer to the current game map.
    void update();    /// This function updates the whole game for one timestep.
private:
    void shootTowers();    /// This function makes all towers attempt to shoot.
    void addMinions();    /// This function adds a new minion to the game periodically
    void moveMinions();    /// This function moves all minions in the right direction.

    int ticksToNextMinion = 3;    /// Temporary variable to determine the period of minion spawning.
    int tickCount = 2;            /// Temporary variable to compare if a new minion should be spawned.
    uint8_t kills = 0;
};


#endif //MINIONCRUSHER_GAMEMANAGER_H
