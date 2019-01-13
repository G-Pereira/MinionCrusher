#include "BuildView.h"

BuildView::BuildView(SDL_Rect quad, UIElement *parent) : UIElement(quad, parent) {
	// add some buttons
	addButton(ButtonTypes::fireTower);

	addButton(ButtonTypes::freezeTower);
}

BuildView::~BuildView() {
}

void BuildView::addButton(ButtonTypes button_type)
{
	UIButton *button1 = new UIButton(nextButtonPosition(), this, button_type);
	button1->loadTexture(RenderElement::texture_lib->GetTexture(TextureLib::TextureEnum::tower1));
	this->addChild(button1);
}

SDL_Rect BuildView::nextButtonPosition()
{
	SDL_Rect retquad = SDL_Rect{ 0 };
	if (children.size() == 0) {
		retquad = SDL_Rect{ button_distance_x, button_distance_y, button_size_x, button_size_y };
	}
	else {
		retquad = children.back()->getQuad();
		if (retquad.x + button_distance_x + retquad.w + button_size_x > quad.w) {
			retquad.x = button_distance_x;
			retquad.y += button_distance_y +  button_size_y;
			retquad.h = button_size_y;
			retquad.w = button_size_x;
		}
		else {
			retquad.x += button_distance_x + button_size_x;
			retquad.h = button_size_y;
			retquad.w = button_size_x;
		}
	}
	return retquad;
}

