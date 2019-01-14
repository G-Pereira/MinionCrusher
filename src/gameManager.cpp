#include "gameManager.h"

GameManager::GameManager() : map(nullptr) {
	this->money = 200;
}

/// Do a full update step. Called periodically to update the whole map.
void GameManager::update() {
	//std::cout << (int)gameState << std::endl;

	switch (gameState) {
	case menu:
	case lost:
		break;
	case start:
		level=0;
		minionsLeftInWave = 5; // TODO: Make it modular, design a level manager
		cooldownTime = 5000;
		gameState = cooldown; // TODO: add condition with a start button
		break;
	case run:
		shootTowers();
		addMinions();
		moveMinions();
		if (map != nullptr) {
			if (minionsLeftInWave <= 0 && map->minions.size() == 0) {
				gameState = cooldown;
				spawnSpeed += 0.01F;
			}
			if (map->base.getHealth() <= 0) {
				gameState = lost;
			}
		}
		break;
	case cooldown:
		cooldownTime--;
		if (cooldownTime <= 0) {
			level++;
			minionsLeftInWave = 5 * level;
			cooldownTime = 2000;
			gameState = run;
		}
		break;
	}
}

void GameManager::startNewGame(std::string map_path)
{
	resetGame();
	map = new Map(map_path);
	gameState = GameManager::start;
}

void GameManager::resetGame() {
	// reset all variables
	delete map;
	map = nullptr;
	money = 500;
	kills = 0;
	level = 0;
	cooldownTime = 0;
	tickCount = 0;
	minionsLeftInWave = 0;
}
bool GameManager::addTower(CartesianCoordinates coordinates, ButtonTypes type)
{
	if (money >= 100) {
		if (map->addTower(coordinates, type)) {
			money -= 100;
			return true;
		}
	}
	else {
		std::cout << "not enough money: " << money << std::endl;
	}
	return false;
}

/// Tell all towers to update, which means they will either shoot or load up to shoot.
void GameManager::shootTowers() {
    for (Tower &tower : map->towers) {
		int bounty = tower.update(map->minions);
		if (bounty != 0) {
			kills++;
			money += bounty;
		}
    }
}


/// Spawn minions based on the determined interval.
void GameManager::addMinions() {
    // Add minions to the battlefield on an interval
    if (spawnSpeed * tickCount >= ticksToNextMinion && minionsLeftInWave > 0) {
        tickCount = 0;
		if (minionsLeftInWave % 2 == 0) {
			Minion minion = MinionRemi(map->spawnPos.x, map->spawnPos.y);
			map->minions.push_back(minion);
			minionsLeftInWave--;
		} else {
			Minion minion = MinionMedium(map->spawnPos.x, map->spawnPos.y);
			map->minions.push_back(minion);
			minionsLeftInWave--;
		}
    } else {
        tickCount++;
    }
}

/// Move all the minions forward on the path based on their speed.
void GameManager::moveMinions() {
    bool finished;
    do {
        finished = true;
        for (Minion &minion : (map->minions)) {

            int dir = (int) map->path[(int) minion.traversedDistance].getType();
            minion.setCoordinates(
                    {minion.getCoordinates().x + minion.speed * (-(dir == 1) + (dir == 4)),
                     minion.getCoordinates().y + minion.speed * (-(dir == 3) + (dir == 2))}
            );
            if (int(minion.traversedDistance) >= (int) map->path.size() - 1) {
                map->base.doDamage(map->minions.front().getDamage());
                map->minions.pop_front();
                finished = false;
                break;
            }
            minion.traversedDistance = minion.traversedDistance + minion.speed;
			if (minion.speed < minion.maxSpeed) {
				minion.speed += (minion.maxSpeed - minion.speed)*0.1F;
			}
        }
    } while (!finished);
}
