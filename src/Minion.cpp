#include "Minion.h"

Minion::Minion(float x, float y, float width, float height, float health, float damage, float speed, int bounty, ObjectType type)
        : MapObject(x, y, width, height, type), health(health), max_health(health), damage(damage), speed(speed) , bounty(bounty){
	maxSpeed = speed;
}

Minion::~Minion() {

}

const float &Minion::getHealth() const {
    return this->health;
}

const float &Minion::getMaxHealth() const {
    return max_health;
}

void Minion::setHealth(float inputHealth) {
    this->health = inputHealth;
    max_health = inputHealth > max_health ? inputHealth : max_health;
}

void Minion::setDamage(float inpDamage) {
    this->damage = inpDamage;
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

constexpr float RELATIVE_HEIGHT = 0.1F;
constexpr float RELATIVE_WIDTH = 0.8F;

void Minion::postRender() {
    if (max_health == 0.0F) {
        std::cerr << "no maximum health set" << std::endl;
        return;
    }
    SDL_Rect health_rect;
    health_rect.w = (int) (quad.w * RELATIVE_WIDTH);
    health_rect.h = (int) (quad.h * RELATIVE_HEIGHT);
    health_rect.x = (int) (quad.x + quad.w * RELATIVE_HEIGHT);
    health_rect.y = (int) (quad.y + quad.h * (1.0F - RELATIVE_HEIGHT));
    SDL_RenderFillRect(renderer, &health_rect);
    SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
    SDL_RenderFillRect(renderer, &health_rect);
    health_rect.w = (int) (health_rect.w * (health > 0 ? health : 0) / max_health);
    SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);
    SDL_RenderFillRect(renderer, &health_rect);
}
