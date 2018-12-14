/*
 * Author: Remi Jonkman
 * Created on: 28-11-18
 * Last Modified: 28-11-18
 */

#include <Tower.h>

#include "Tower.h"

Tower::Tower(float x, float y, float width, float height, int firePeriod, float range, float damage, AmmoType ammo)
        : MapObject(x, y, width, height), firePeriod(firePeriod), range(range), damage(damage), ammo(ammo) {

}

Tower::~Tower() {

}

void Tower::update(std::list<Minion> &minions)
{
	if (ticks >= firePeriod) {
		for (Minion &minion : minions) {
			if (minion.getCoordinates().isInRange(coordinates, range)) {
				minion.setHealth(minion.getHealth() - damage);
				ticks = 0;
				if (minion.getHealth() <= 0)
					minions.remove(minion);
				break;
			}
		}
	}
	else {
		ticks++;
	}
	
}

const int &Tower::getFirePeriod() const {
    return firePeriod;
}

void Tower::setFirePeriod(int firePeriod) {
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

const float &Tower::getRange() const {
    return range;
}

void Tower::setRange(float range) {
    Tower::range = range;
}

const int &Tower::getTicks() const {
    return ticks;
}

void Tower::setTicks(int ticks) {
    Tower::ticks = ticks;
}
