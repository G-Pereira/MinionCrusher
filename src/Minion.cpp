/**
 * Author: Remi Jonkman
 * Created on: 28-11-18
 * Last Modified: 28-11-18
 */

#include "Minion.h"

Minion::Minion(float x, float y, float width, float height, float health, float damage, float speed)
        : MapObject(x, y, width, height), health(health), max_health(health), damage(damage), speed(speed) {

}

Minion::~Minion() {

}

const float &Minion::getHealth() const {
    return this->health;
}

const float & Minion::getMaxHealth() const
{
	return max_health;
}

void Minion::setHealth(float health) {
    this->health = health;
	max_health = health > max_health ? health : max_health;
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