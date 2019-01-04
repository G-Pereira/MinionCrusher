#pragma once
#ifndef MINIONCRUSHER_MAPVIEW_H
#define MINIONCRUSHER_MAPVIEW_H

#pragma warning( push )
#include <mutex>
#pragma warning( pop )

#include "UIElement.h"
#include "Map.h"


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
     *Set a new map in the view to use
     * @param: map a pointer to the new map
     */
    void setMap(Map *);

private:
    Map *map;
    float tilewidth;
    float tileheight;
	/**
	 * return the shape the healthbar should have
	 */
    SDL_Rect getHealthbar();
};


#endif