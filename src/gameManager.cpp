#include "gameManager.h"

std::mutex GameManager::key;

GameManager::GameManager() : map(nullptr) {
    this->money = 500;
}

void GameManager::update() {
    //std::lock_guard<std::mutex> guard(GameManager::key);
    std::cout << "Updating Game" << std::endl;
    if (gameState == start) {
        level = 1;
        minionsLeftInWave = 5; // TODO: Make it modular, design a level manager
        cooldownTime = 1000;
        gameState = run; // TODO: add condition with a start button
    }
    if (gameState == run) {
        shootTowers();
        addMinions();
        moveMinions();
    }
    if (gameState == cooldown) {
        cooldownTime--;
        if (cooldownTime <= 0) {
            level++;
            minionsLeftInWave = 5 * level;
            cooldownTime = level * 1000;
            gameState = run;
        }
    }
    if (minionsLeftInWave <= 0 && map->getMinions().size() == 0) gameState = cooldown;
    if (map->getBase().getHealth() <= 0) gameState = lost;
}

bool GameManager::addTower(CartesianCoordinates coordinates) {
    if (money >= 100) {
        money -= 100;
        map->addTower(coordinates);
        std::cout << money << std::endl;
        return true;
    }
    return false;
}

void GameManager::shootTowers() {
    for (Tower &tower : map->getTowers()) {
        int bounty = tower.update(map->getMinions());
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
    if (speed * tickCount >= ticksToNextMinion && minionsLeftInWave > 0) {
        tickCount = 0;
        Minion minion = MinionRemi(map->getSpawn().x, map->getSpawn().y);
        map->getMinions().push_back(minion);
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
        for (Minion &minion : (map->getMinions())) {

            int dir = (int) map->getPath()[(int) minion.traversedDistance].getType();
            minion.setCoordinates(
                    {minion.getCoordinates().x + minion.getSpeed() * (-(dir == 1) + (dir == 4)),
                     minion.getCoordinates().y + minion.getSpeed() * (-(dir == 3) + (dir == 2))}
            );
            if (int(minion.traversedDistance) >= (int) map->getPath().size() - 1) {
                map->getBase().doDamage(map->getMinions().front().getDamage());
                map->getMinions().pop_front();
                finished = false;
                break;
            }
            minion.traversedDistance = minion.traversedDistance + minion.getSpeed();
        }
    } while (!finished);
}
