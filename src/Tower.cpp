/**
 * Author: Remi Jonkman
 * Created on: 28-11-18
 * Last Modified: 28-11-18
 */

#include "Tower.h"

Tower::Tower(float x, float y, float width, float height, float health, float speed, float damage, AmmoType ammo)
        : MapObject(x, y, width, height), health(health), speed(speed), damage(damage), ammo(ammo) {

}

Tower::~Tower() {

}

const float &Tower::getHealth() const {
    return health;
}

void Tower::setHealth(float health) {
    Tower::health = health;
}

const float &Tower::getSpeed() const {
    return speed;
}

void Tower::setSpeed(float speed) {
    Tower::speed = speed;
}

const float &Tower::getDamage() const {
    return damage;
}

void Tower::setDamage(float damage) {
    Tower::damage = damage;
}

const AmmoType &Tower::getAmmo() const {
    return ammo;
}

void Tower::setAmmo(AmmoType ammo) {
    Tower::ammo = ammo;
}
