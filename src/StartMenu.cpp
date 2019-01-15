#include "StartMenu.h"


StartMenu::StartMenu(SDL_Rect viewport, UIElement *parent) : UIElement(viewport, parent) {
    button_distance_x = 100;
    button_distance_y = 100;
    button_size_x = 500;
    button_size_y = 100;
    loadTexture(texture_lib->GetTexture(TextureLib::TextureEnum::menu));
    addButton(ButtonTypes::startmap1);
    addButton(ButtonTypes::startmap2);
}


StartMenu::~StartMenu() {
}

void StartMenu::addButton(ButtonTypes button_type) {
    UIButton *button1 = new UIButton(nextAutoButtonPosition(), this, button_type);
    switch (button_type) {
        case ButtonTypes::startmap1:
            button1->loadText2Texture("Start level 1");
            button_type = ButtonTypes::idle;
            break;
        case ButtonTypes::startmap2:
            button1->loadText2Texture("Start level 2");
            button_type = ButtonTypes::idle;
            break;
    }
    this->addChild(button1);
}
