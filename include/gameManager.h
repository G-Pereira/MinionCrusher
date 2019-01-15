#ifndef MINIONCRUSHER_GAMEMANAGER_H
#define MINIONCRUSHER_GAMEMANAGER_H

#include "Map.h"
#include "types.h"

/**
 * Needs to be called every tick to update the game. Will update towers, minions, etc.
 * */
class GameManager {
public:
    /**
     * Game Manager
     */
    GameManager();

    /**
     * Player's current money
     */
    int money;

    /**
     * Pointer to the current game map.
     */
    Map *map;

    /**
     * This function updates the whole game for one timestep.
     */
    void update();

    /**
     * Adds a Tower to the Map
     * @param coordinates where to place the Tower
     * @param type Type of entity
     * @return Returns if tower was placed or not according to current Player's money
     */
    bool addTower(CartesianCoordinates coordinates, ButtonTypes type);

    /**
     * Player's Minion kills
     */
    int kills = 0;

    /**
     * Leve the Player is currently at
     */
    int level = 0;

    /**
     * Time between waves
     */
    int cooldownTime = 0;

    /**
     * Minion's spawn speed
     */
    float spawnSpeed = 0.2F;

    /**
     * All the states of the Game
     */
    enum state {
        menu, run, pause, lost, won, start, cooldown
    };

    /***
     * State of the Game
     */
    state gameState = menu;

    /**
     * Starts a new Game
     * @param map_path Map path
     */
    void startNewGame(std::string map_path);

    /**
     * Resets the Game
     */
    void resetGame();

private:
    /**
     * This function makes all towers attempt to shoot.
     */
    void shootTowers();

    /**
     * This function adds a new minion to the game periodically
     */
    void addMinions();

    /**
     * This function moves all minions in the right direction.
     */
    void moveMinions();

    /**
     * Temporary variable to determine the period of minion spawning.
     */
    int ticksToNextMinion = 30;

    /**
     * Temporary variable to compare if a new minion should be spawned.
     */
    int tickCount = 0;

    /**
     * Number of minions between cooldowns
     */
    int minionsLeftInWave = 0;
};


#endif //MINIONCRUSHER_GAMEMANAGER_H
