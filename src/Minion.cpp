/**
 * Author: Remi Jonkman
 * Created on: 28-11-18
 * Last Modified: 28-11-18
 */

#include "Minion.h"

Minion::Minion(float x, float y, float width, float height, float health, float damage, float speed)
	: MapObject(x, y, width, height), health(health), damage(damage), speed(speed) {

}

Minion::~Minion() {

}

const float &Minion::getHealth() const {
    return this->health;
}

void Minion::setHealth(float health) {
    this->health = health;
}

void Minion::setSpeed(float speed) {
    this->speed = speed;
}

const float &Minion::getSpeed() const {
    return this->speed;
}

void Minion::setDamage(float damage) {
    this->damage = damage;
}

const float &Minion::getDamage() const {
    return this->damage;
}