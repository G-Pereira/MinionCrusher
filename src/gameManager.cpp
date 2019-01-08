#include "gameManager.h"

GameManager::GameManager() : map(nullptr) {
	this->money = 500;
}

void GameManager::update() {
    shootTowers();
    addMinions();
    moveMinions();
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
        Minion minion = Medium(map->spawnPos.x, map->spawnPos.y);
        map->minions.push_back(minion);
        speed = minion.getSpeed();
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
