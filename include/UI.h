/**
 * This is the top level of the UI,
 * it will be the top parent and opens either the menu or shows the game,
 * it also has the job of initializing SDL and loading Texturelib
 */
#pragma once
#ifndef MINIONCRUSHER_UI_H
#define MINIONCRUSHER_UI_H

#include <string>

#include "MapView.h"
#include "UIButton.h"
#include "BuildView.h"
#include "InfoView.h"
#include "StartMenu.h"

class UI : public UIElement {
public:
    /**
     * Constructor
     * @param w width in pixels
     * @param h height in pixels
     */
    UI(int w, int h);

    /// Destructor of the UI, calls the UI close method
    ~UI();

    /// push the build frame to the front
    void postRender() override;

    /**
     * returns a pointer to the renderer
     * @return pointer to the used renderer
     */
    SDL_Renderer *getRenderer() const;

private:
    enum class states {
        ingame,
        inmenu
    } state;

    /// Initilialize the inGame UI
    void inGame();

    /// Initilialize the startmenu UI
    void startMenu();

    enum class elements : int {
        map,
        building,
        info
    };
};

#endif