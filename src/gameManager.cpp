#include "gameManager.h"

GameManager::GameManager() : map(nullptr) {
	this->money = 500;
}

void GameManager::update() {
    if(gameState == start){
        level = 1;
        minionsLeftInWave = 5; // TODO: Make it modular, design a level manager
        cooldownTime = 100;
        gameState = run; // TODO: add condition with a start button
    }
    if(gameState == run){
        shootTowers();
        addMinions();
        moveMinions();
    }
    if (gameState == cooldown){
        shootTowers();
        moveMinions();
        if(map->minions.size()==0){
            if(cooldownTime == 0){
                level++;
                minionsLeftInWave = 5 * level;
                cooldownTime = level * 100;
                gameState = run;
            }
            cooldownTime--;
        }
    }
    if(minionsLeftInWave <= 0) gameState = cooldown;
    if (map->base.getHealth() <=0) gameState = lost;
}

bool GameManager::addTower(CartesianCoordinates coordinates)
{
	if (money >= 100) {
		money -= 100;
		map->addTower(coordinates);
		std::cout << money << std::endl;
		return true;
	}
	return false;
}

void GameManager::shootTowers() {
    for (Tower &tower : map->towers) {
		int bounty = tower.update(map->minions);
		if (bounty != 0) {
			kills++;
			money += bounty;
			std::cout << money << std::endl;
		}
    }
}

void GameManager::addMinions() {
    // Add minions to the battlefield on an interval
    static float speed = 0.1F;
    if (speed * tickCount >= ticksToNextMinion) {
        tickCount = 0;
        Minion minion = MinionRemi(map->spawnPos.x, map->spawnPos.y);
        map->minions.push_back(minion);
        speed = minion.getSpeed();
        minionsLeftInWave--;
    } else {
        tickCount++;
    }
}

void GameManager::moveMinions() {
    bool finished;
    do {
        finished = true;
        for (Minion &minion : (map->minions)) {

            int dir = (int) map->path[(int) minion.traversedDistance].getType();
            minion.setCoordinates(
                    {minion.getCoordinates().x + minion.getSpeed() * (-(dir == 1) + (dir == 4)),
                     minion.getCoordinates().y + minion.getSpeed() * (-(dir == 3) + (dir == 2))}
            );
            if (int(minion.traversedDistance) >= (int) map->path.size() - 1) {
                map->base.doDamage(map->minions.front().getDamage());
                map->minions.pop_front();
                finished = false;
                break;
            }
            minion.traversedDistance = minion.traversedDistance + minion.getSpeed();
        }
    } while (!finished);
}
