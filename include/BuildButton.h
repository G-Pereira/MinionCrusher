#pragma once
#include "UIButton.h"

class BuildButton :public UIButton {
public:
	BuildButton(SDL_Rect quad, void funct(UIButton & self, SDL_Event &), UIElement * parent);

	void HandleEvents(SDL_Event &e) override;
};