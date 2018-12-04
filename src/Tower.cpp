/**
 * Author: Remi Jonkman
 * Created on: 28-11-18
 * Last Modified: 28-11-18
 */

#include "Tower.h"

Tower::Tower(float x, float y, float width, float height, float firePeriod, float range, float damage, AmmoType ammo)
        : MapObject(x, y, width, height), firePeriod(firePeriod), range(range), damage(damage), ammo(ammo) {

}

Tower::~Tower() {

}

const float &Tower::getFirePeriod() const {
    return firePeriod;
}

void Tower::setFirePeriod(float firePeriod) {
    Tower::firePeriod = firePeriod;
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
