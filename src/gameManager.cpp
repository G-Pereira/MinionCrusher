#include "gameManager.h"

GameManager::GameManager() 
{
}

void GameManager::update()
{
	shootTowers();
	addMinions();
	moveMinions();
}

void GameManager::shootTowers()
{
	for (Tower &tower : map->towers) {
		tower.update(map->minions);
	}
}

void GameManager::addMinions()
{
	// Add minions to the battlefield on an interval
	static float speed = 0.1F;
	if (speed * tickCount >= ticksToNextMinion) {
		tickCount = 0;
		Minion minion = Minion(map->spawnPos.x, map->spawnPos.y, 1, 1, 100, 1, 0.02F);
		map->minions.push_back(minion);
		speed = minion.getSpeed();
	}
	else {
		tickCount++;
	}
}

void GameManager::moveMinions()
{
	bool finished;
	do {
		finished = true;
		for (Minion &minion : (map->minions)) {

			int dir = (int)map->path[(int)minion.traversedDistance].getType();
			minion.setCoordinates(
				{ minion.getCoordinates().x + minion.getSpeed() * (-(dir == 1) + (dir == 4)),
				 minion.getCoordinates().y + minion.getSpeed() * (-(dir == 3) + (dir == 2)) }
			);
			if (int(minion.traversedDistance) >= (int)map->path.size() - 1) {
				map->base.doDamage(map->minions.front().getDamage());
				map->minions.pop_front();
				finished = false;
				break;
			}
			minion.traversedDistance = minion.traversedDistance + minion.getSpeed();
		}
	} while (!finished);
}
