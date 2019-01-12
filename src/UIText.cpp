
#include "UIText.h"

UIText::UIText(SDL_Rect quad, UIElement *parent, UIText::info_types type) :
        UIElement(quad, parent), type(type) {
}

UIText::~UIText() {
}

void UIText::postRender() {
    switch (type) {
        case info_types::health:
            if (prev_value != gamemanager->map->base.getHealth()) {
                std::string disp = "health: " + std::to_string((int) gamemanager->map->base.getHealth());
                quad.w = (int) disp.size()*quad.h/2;
                loadText2Texture(disp);
                prev_value = gamemanager->map->base.getHealth();
            }
            break;
        case info_types::kills:
            if (prev_value != gamemanager->kills) {
                std::string disp = "kills: " + std::to_string(gamemanager->kills);
                quad.w = (int) disp.size()*quad.h/2;
                loadText2Texture(disp);
                prev_value = gamemanager->kills;
            }
            break;
        case info_types::money:
            if (prev_value != gamemanager->money) {
                std::string disp = "money: " + std::to_string(gamemanager->money);
                quad.w = (int) disp.size()*quad.h/2;
                loadText2Texture(disp);
                prev_value = gamemanager->money;
            }
            break;
        case info_types::level:
            if (prev_value != gamemanager->level) {
                std::string disp = "level: " + std::to_string(gamemanager->level);
                quad.w = (int) disp.size()*quad.h/2;
                loadText2Texture(disp);
                prev_value = gamemanager->level;
            }
            break;
        case info_types::state:
            if (prev_value != gamemanager->cooldownTime) {
                std::string disp = "cooldown: " + std::to_string(gamemanager->cooldownTime / 500) + "s";
                quad.w = (int) disp.size()*quad.h/2;
                loadText2Texture(disp);
                prev_value = gamemanager->cooldownTime;
            }
            break;
        default:
            break;
    }
}
