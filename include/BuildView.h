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
	int button_distance_x = 20;
	int button_distance_y = 20;
	int button_size_x = 100;
	int button_size_y = 100;

	SDL_Rect nextButtonPosition();
};

