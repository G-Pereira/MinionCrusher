#pragma once
#include "UIElement.h"
class BuildView :
	public UIElement
{
public:
	BuildView(SDL_Rect, UIElement * parent);
	~BuildView();
	void preRender();
};

