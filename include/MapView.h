#pragma once
#ifndef MINIONCRUSHER_MAPVIEW_H
#define MINIONCRUSHER_MAPVIEW_H

#include "UIView.h"


class MapView : public UIView {
public:
	MapView(SDL_Rect, UIView * parent);
	~MapView();
	void preRender();
	void postRender();
	void setMap(Map *);

	Map *map;
private:

	float tilewidth;
	float tileheight;
};


#endif