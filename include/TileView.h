#pragma once

#include "UIView.h"
#include "PathTile.h"

class TileView:UIView
{
public:
	TileView(SDL_Rect, MapSlots type);
	~TileView();
	void Render();

	const MapSlots type;

};

