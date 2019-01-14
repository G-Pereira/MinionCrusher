#pragma once

#include "UIElement.h"
#include "UIButton.h"
/**
 * holds the buttons and information about the buildings
 */
class BuildView :
        public UIElement {
public:
    BuildView(SDL_Rect, UIElement *parent);

    ~BuildView();

	void addButton(ButtonTypes button_type);
private:
};

