#ifndef MINIONCRUSHER_GAMEMANAGER_H
#define MINIONCRUSHER_GAMEMANAGER_H

#include "Map.h"
#include "types.h"


/** Needs to be called every tick to update the game. Will update towers, minions, etc. */
class GameManager {
public:
    GameManager();

	int money;
    Map *map;        /// Pointer to the current game map.
    void update();    /// This function updates the whole game for one timestep.
	bool addTower(CartesianCoordinates coordinates, ButtonTypes type);
	int kills = 0;
	int level = 0;
	int cooldownTime = 0;
	float spawnSpeed = 0.2F;
	enum state { menu, run, pause, lost, won, start, cooldown };		/// Game states
	state gameState = menu;
	void startNewGame(std::string map_path);
	void resetGame();
private:
    void shootTowers();			/// This function makes all towers attempt to shoot.
    void addMinions();			/// This function adds a new minion to the game periodically
    void moveMinions();			/// This function moves all minions in the right direction.

    int ticksToNextMinion = 30;	/// Temporary variable to determine the period of minion spawning.
    int tickCount = 0;			/// Temporary variable to compare if a new minion should be spawned.
    int minionsLeftInWave = 0;	/// Number of minions between cooldowns
};


#endif //MINIONCRUSHER_GAMEMANAGER_H
