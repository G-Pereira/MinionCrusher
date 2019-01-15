/**
 * MapView is the UIElement used while in game to show all objects on the map
 */

#pragma once
#ifndef MINIONCRUSHER_MAPVIEW_H
#define MINIONCRUSHER_MAPVIEW_H

#include <mutex>

#include "UIElement.h"


class MapView : public UIElement {
public:
    MapView(SDL_Rect, UIElement *parent);

    ~MapView();

    /**
     * Override the standard postRender to render the map elements
     * @param: map a pointer to the new map
     */
    void postRender() override;

	/**
	 *
	 * @param:
	 */
	static int mapClick(void* data, SDL_Event * e);


private:
    float tilewidth;
    float tileheight;
	/**
	 * return the shape the healthbar should have
	 */
    SDL_Rect getHealthbar();
};


#endif