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

bool Minion::operator==(const Minion &rhs) const {
    return traversedDistance == rhs.traversedDistance &&
           health == rhs.health &&
           max_health == rhs.max_health &&
           damage == rhs.damage &&
           speed == rhs.speed;
}

bool Minion::operator!=(const Minion &rhs) const {
    return !(rhs == *this);
}
