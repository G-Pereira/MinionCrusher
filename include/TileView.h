/**
 * Author: Leon Klute
 * Created on: 04-12-18
 * Last Modified: 04-12-18
 */
#pragma once

#include "UIView.h"
#include "PathTile.h"

class TileView:public UIView
{
public:
	TileView(SDL_Rect, MapSlots type, UIView * parent);
	~TileView();
	void postRender();

	const MapSlots type;

};

