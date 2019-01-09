
#include "UIText.h"

UIText::UIText(SDL_Rect quad, UIElement *parent, UIText::info_types type) :
        UIElement(quad, parent), type(type) {
}

UIText::~UIText() {
}

void UIText::postRender()
{
	switch (type) {
	case info_types::health:
		if (prev_health != gamemanager->map->base.getHealth()) {
			loadText2Texture("health: " + std::to_string((int)gamemanager->map->base.getHealth()));
			prev_health = gamemanager->map->base.getHealth();
		}
		break;
	case info_types::kills:
		if (prev_kills != gamemanager->kills) {
			loadText2Texture("kills: " + std::to_string(gamemanager->kills));
			prev_kills = gamemanager->kills;
		}
		break;
	case info_types::money:
		if (prev_money != gamemanager->money) {
			loadText2Texture("money: " + std::to_string(gamemanager->money));
			prev_money = gamemanager->money;
		}
		break;
	default:
		break;
	}
}
