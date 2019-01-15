#pragma once

#include "UIElement.h"
#include "UIButton.h"

/**
 * Holds the buttons and information about the buildings
 */
class BuildView :
        public UIElement {
public:
    /**
     * Build View
     * @param parent Container to insert the build view
     */
    BuildView(SDL_Rect, UIElement *parent);

    ~BuildView();

    /**
     * Add a button to the Build View
     * @param button_type Type of button
     */
    void addButton(ButtonTypes button_type);

private:
};

