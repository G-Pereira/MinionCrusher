#pragma once
#ifndef MINIONCRUSHER_MAPVIEW_H
#define MINIONCRUSHER_MAPVIEW_H

#include "UIView.h"


class MapView : public UIView {
	MapView(SDL_Rect);
	~MapView();
	bool setMap(Map *);

	Map *map;
};


#endif