#pragma once

#include "UIElement.h"

/**
 * holds the buttons and information about the buildings
 */
class BuildView :
        public UIElement {
public:
    BuildView(SDL_Rect, UIElement *parent);

    ~BuildView();
};

