#include <Tower.h>

Tower::Tower(float x, float y, float width, float height, int firePeriod, float range, Ammo ammo, ObjectType type)
        : MapObject(x, y, width, height, type), firePeriod(firePeriod), range(range), ammo(ammo),
          target(SDL_Rect{-1, -1, -1, -1}) {

}

Tower::~Tower() {

}

int Tower::update(std::list <Minion> &minions) {
    if (ticks >= firePeriod) {
        for (Minion &minion : minions) {
            if ((minion.getCoordinates() - coordinates).abs() < range) {
                target = minion.getQuad();
                minion.setHealth(minion.getHealth() - this->ammo.damage);
                minion.speed = minion.speed * ammo.slow;
                ticks = 0;
                if (minion.getHealth() <= 0) {
                    int bounty = minion.bounty;
                    minions.remove(minion);
                    return bounty;
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

void Tower::setFirePeriod(int inpFirePeriod) {
    Tower::firePeriod = inpFirePeriod;
}

const float &Tower::getDamage() const {
    return ammo.damage;
}

const Ammo &Tower::getAmmo() const {
    return ammo;
}

void Tower::setAmmo(Ammo inpAmmo) {
    Tower::ammo = inpAmmo;
}

const float &Tower::getRange() const {
    return range;
}

void Tower::setRange(float inpRange) {
    Tower::range = inpRange;
}

const int &Tower::getTicks() const {
    return ticks;
}

void Tower::setTicks(int inpTicks) {
    Tower::ticks = inpTicks;
}

void Tower::postRender() {
    float timepassed = (float) ticks / (float) firePeriod;
    int8_t alpha = SDL_ALPHA_OPAQUE * (1.0f - timepassed);
    switch (objectType) {
        case ObjectType::TOWER1:
            SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, alpha);
            break;
        case ObjectType::TOWER2:
            SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, alpha);
            break;
    }
    if (target.x >= 0)
        SDL_RenderDrawLine(renderer, quad.x + quad.w / 2, quad.y + quad.h / 2, target.x + target.w / 2,
                           target.y + target.h / 2);
}
