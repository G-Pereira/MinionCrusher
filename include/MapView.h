#pragma once
#ifndef MINIONCRUSHER_MAPVIEW_H
#define MINIONCRUSHER_MAPVIEW_H

#include <mutex>

#include "UIElement.h"
#include "Map.h"
#include "TileView.h"


class MapView : public UIElement {
public:
	MapView(SDL_Rect, UIElement * parent);
	~MapView();
	void postRender(SDL_Renderer * renderer) override;
	void setMap(Map *);
	Map *map;
private:
	float tilewidth;
	float tileheight;
	SDL_Rect getHealthbar();
};


#endif