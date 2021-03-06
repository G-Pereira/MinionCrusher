#include "BuildView.h"

BuildView::BuildView(SDL_Rect quad, UIElement *parent) : UIElement(quad, parent) {
    loadTexture(RenderElement::texture_lib->GetTexture(TextureLib::TextureEnum::building_background));
    // add some buttons
    addButton(ButtonTypes::fireTower);

    addButton(ButtonTypes::freezeTower);
}

BuildView::~BuildView() {
}

void BuildView::addButton(ButtonTypes button_type) {
    UIButton *button1 = new UIButton(nextAutoButtonPosition(), this, button_type);
    switch (button_type) {
        case ButtonTypes::fireTower:
            button1->loadTexture(RenderElement::texture_lib->GetTexture(TextureLib::TextureEnum::tower1));
            break;
        case ButtonTypes::freezeTower:
            button1->loadTexture(RenderElement::texture_lib->GetTexture(TextureLib::TextureEnum::tower2));
            break;
        case ButtonTypes::idle:
            break;
        case ButtonTypes::startmap1:
            break;
        case ButtonTypes::startmap2:
            break;
        case ButtonTypes::pause:
            break;
        default:
            break;
    }
    this->addChild(button1);
}


