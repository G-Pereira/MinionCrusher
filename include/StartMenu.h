#pragma once
#include "UIButton.h"
class StartMenu :
	public UIElement
{
public:
	StartMenu(SDL_Rect viewport, UIElement *parent);
	~StartMenu();
private:
	void addButton(ButtonTypes button_type);
};

