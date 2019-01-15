#include "Base.h"

Base::Base(float x, float y, float width, float height, float health)
        : MapObject(x, y, width, height, ObjectType::BASE), health(health), max_health(health) {

}

Base::~Base() {

}

const float &Base::getHealth() const {
    return this->health;
}

void Base::setHealth(float inputHealth) {
    max_health = inputHealth > max_health ? inputHealth : max_health;
    this->health = inputHealth;
}

void Base::doDamage(float damage) {
    this->health -= damage;
}

constexpr float RELATIVE_HEIGHT = 0.1F;
constexpr float RELATIVE_WIDTH = 0.8F;

void Base::postRender() {
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