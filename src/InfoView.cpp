#include "InfoView.h"


InfoView::InfoView(SDL_Rect quad, UIElement *parent) : UIElement(quad, parent){

	SDL_Rect text_quad = SDL_Rect{ 30, 30, 150, 30 };
	UIText *text_health = new UIText(text_quad, this, UIText::info_types::health);
	addChild(text_health);

	text_quad.y += 50;
	UIText *text_kills = new UIText(text_quad, this, UIText::info_types::kills);
	addChild(text_kills);

	text_quad.y -= 50;
	text_quad.x += text_quad.w + 50;
	UIText *text_money = new UIText(text_quad, this, UIText::info_types::money);
	addChild(text_money);

	text_quad.x = quad.w-text_quad.w-50;
	UIText *text_level = new UIText(text_quad, this, UIText::info_types::level);
	addChild(text_level);

	text_quad.y += 50;
	UIText *text_cooldown = new UIText(text_quad, this, UIText::info_types::state);
	addChild(text_cooldown);
}

InfoView::~InfoView() {
    SDL_DestroyTexture(background);
}
