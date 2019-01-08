/*
 * Author: Remi Jonkman
 * Created on: 28-11-18
 * Last Modified: 28-11-18
 */

#include <Tower.h>

Tower::Tower(float x, float y, float width, float height, int firePeriod, float range, float damage, AmmoType ammo)
        : MapObject(x, y, width, height), firePeriod(firePeriod), range(range), damage(damage), ammo(ammo)
	, rangeSquared(range*range), target(SDL_Rect{ (int)x, (int)y, (int)width, (int)height }) {

}

Tower::~Tower() {

}

uint8_t Tower::update(std::list<Minion> &minions) {
    if (ticks >= firePeriod) {
        for (Minion &minion : minions) {
            if (minion.getCoordinates().isInRange(coordinates, range)) {
				target = minion.getQuad();
                minion.setHealth(minion.getHealth() - damage);
                ticks = 0;
                if (minion.getHealth() <= 0) {
                    minions.remove(minion);
                    return 1;
                }
                break;
            }
        }
    } else {
        ticks++;
    }
    return 0;
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

void Tower::postRender()
{
	float timepassed = (float)ticks / (float)firePeriod;
	int8_t alpha = SDL_ALPHA_OPAQUE * (1.0f - timepassed);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, alpha);
	SDL_RenderDrawLine(renderer, quad.x + quad.w / 2, quad.y + quad.h / 2, target.x + target.w / 2, target.y + target.h / 2);
}
