/**
 * StartMenu is the UIelement that is visible when you can start a new game
 * it has some buttons to choose from, which it loads itself
 */
#pragma once

#include "UIButton.h"

class StartMenu :
        public UIElement {
public:
    StartMenu(SDL_Rect viewport, UIElement *parent);

    ~StartMenu();

private:
    void addButton(ButtonTypes button_type);
};

