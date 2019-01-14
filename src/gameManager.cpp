#include "gameManager.h"

GameManager::GameManager() : map(nullptr) {
	this->money = 200;
}

void GameManager::update() {
    if(gameState == start){
        level = 1;
        minionsLeftInWave = 5; // TODO: Make it modular, design a level manager
        cooldownTime = 1000;
        gameState = run; // TODO: add condition with a start button
    }

    if(gameState == run){
        shootTowers();
        addMinions();
        moveMinions();
		if (minionsLeftInWave <= 0 && map->minions.size() == 0) {
			gameState = cooldown;
			spawnSpeed += 0.01;
			std::cout << spawnSpeed << std::endl;
		}
    }

    if (gameState == cooldown){
        cooldownTime--;
        if (cooldownTime <= 0){
            level++;
            minionsLeftInWave = 5 * level;
            cooldownTime = 2000;
            gameState = run;
		}
    }
	
	if (map->base.getHealth() <= 0) {
		gameState = lost;
		std::cout << "Game Lost" << std::endl;
	}
}

bool GameManager::addTower(CartesianCoordinates coordinates, ButtonTypes type)
{
	if (money >= 100) {
		money -= 100;
		map->addTower(coordinates, type);
		return true;
	}
	std::cout << "not enough money: " << money << std::endl;
	return false;
}

void GameManager::shootTowers() {
    for (Tower &tower : map->towers) {
		int bounty = tower.update(map->minions);
		if (bounty != 0) {
			kills++;
			money += bounty;
			//std::cout << money << std::endl;
		}
    }
}

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
