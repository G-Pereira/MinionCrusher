#include "InfoView.h"


InfoView::InfoView(SDL_Rect quad, UIElement *parent) : UIElement(quad, parent){

	SDL_Rect text_quad = SDL_Rect{ 30, 30, 150, 30 };
	UIText *text_health = new UIText(text_quad, this, UIText::info_types::health);
	addChild(text_health);

	text_quad.y += 50;
	UIText *text_kills = new UIText(text_quad, this, UIText::info_types::kills);
	addChild(text_kills);

}

InfoView::~InfoView() {
    SDL_DestroyTexture(background);
}
