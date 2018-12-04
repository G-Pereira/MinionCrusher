#pragma once
#include "UIView.h"
class BuildView :
	public UIView
{
public:
	BuildView(SDL_Rect, UIView * parent);
	~BuildView();
	void preRender();
};

