/**
 * Author: Leon Klute
 * Created on: 26-11-18
 * Last Modified: 28-11-18
 */
#pragma once
#ifndef MINIONCRUSHER_UI_H
#define MINIONCRUSHER_UI_H

#include <string>

#include "MapView.h"
#include "BuildButton.h"
#include "BuildView.h"
#include <InfoView.h>

class UI : public UIElement {
public:
    /**
     * Constructor
     * @param w width in pixels
     * @param h height in pixels
     */
    UI(int w, int h);

    /**
     * Destructor of the UI, calls the UI close method
     */
    ~UI();

    /**
     * Initilialize the UI
     */
    void init();

    void postRender() override;

    /**
     * returns a pointer to the renderer
     * @return pointer to the used renderer
     */
    SDL_Renderer *getRenderer() const;

    /**
    * Set the map in the appropriate UI Element
    */
    void setMap(Map *);

private:
    /**
     * Perform all closing action to clean the memory of the UI
     */
    //SDL_Renderer *renderer;
    enum class elements : int {
        map,
        building,
        info
    };
    SDL_Window *window;
};

#endif