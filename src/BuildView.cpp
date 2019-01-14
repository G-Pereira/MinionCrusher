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
	UIButton *button1 = new UIButton(nextAutoButtonPosition(), this, button_type);
	switch (button_type) {
	case ButtonTypes::fireTower:
		button1->loadTexture(RenderElement::texture_lib->GetTexture(TextureLib::TextureEnum::tower1));
		break;
	case ButtonTypes::freezeTower:
		button1->loadTexture(RenderElement::texture_lib->GetTexture(TextureLib::TextureEnum::tower2));
		break;
	}
	this->addChild(button1);
}


