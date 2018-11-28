/**
 * Author: Remi Jonkman
 * Created on: 28-11-18
 * Last Modified: 28-11-18
 */

#include "Bullet.h"

Bullet::Bullet(float x, float y, float width, float height, AmmoType ammo)
    : MapObject(x, y, width, height), ammo(ammo) {

}

Bullet::~Bullet() {

}

const AmmoType &Bullet::getAmmo() const {
    return ammo;
}

void Bullet::setAmmo(AmmoType ammo) {
    Bullet::ammo = ammo;
}
