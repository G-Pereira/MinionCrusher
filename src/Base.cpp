/**
 * Author: Remi Jonkman
 * Created on: 28-11-18
 * Last Modified: 28-11-18
 */

#include "Base.h"

Base::Base(float x, float y, float width, float height, float health)
        : MapObject(x, y, width, height), health(health) {

}

Base::~Base() {

}

const float &Base::getHealth() const {
    return this->health;
}

void Base::setHealth(float health) {
    this->health = health;
}

void Base::doDamage(float damage) {
    this->health -= damage;
}
