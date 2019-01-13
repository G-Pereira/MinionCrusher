/**
 * Author: Leon Klute
 * Created on: 26-11-18
 * Last Modified: 28-11-18
 */
#pragma once
#ifndef MINIONCRUSHER_UI_H
#define MINIONCRUSHER_UI_H

#include <string>
#include <mutex>
#include "MapView.h"
#include "UIButton.h"
#include "BuildView.h"
#include "InfoView.h"

class UI : public UIElement {
public:
    /**
     * Constructor
     * @param w width in pixels
     * @param h height in pixels
     */
    UI(int w, int h);

    /**
     * Copy constructor
     */
    //UI(const UI& ui);

    /**
     * Destructor of the UI, calls the UI close method
     */
    ~UI();

    /**
     * Initilialize the UI
     */
    void init();

    void render() override;

	/**
	 * push the build frame to the front
	 */
    void postRender() override;

    /**
     * returns a pointer to the renderer
     * @return pointer to the used renderer
     */
    SDL_Renderer *getRenderer() const;
	
private:
    // Mutex locking key
    static std::mutex key;

    enum class elements : int {
        map,
        building,
        info
    };
    SDL_Window *window;
};

#endif