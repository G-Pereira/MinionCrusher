/**
 * Author: Leon Klute
 * Created on: 04-12-18
 * Last Modified: 04-12-18
 */
#pragma once

#include "UIElement.h"
#include "PathTile.h"

class TileView:public UIElement
{
public:
	TileView(SDL_Rect, MapSlots type, UIElement * parent);
	~TileView();
	void postRender();

	const MapSlots type;

};

