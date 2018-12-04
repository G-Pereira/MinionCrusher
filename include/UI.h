/**
 * Author: Leon Klute
 * Created on: 26-11-18
 * Last Modified: 28-11-18
 */
#pragma once
#ifndef MINIONCRUSHER_UI_H
#define MINIONCRUSHER_UI_H

#include <SDL.h>
#include <string>
#include <vector>
#include "MapObject.h"
#include "UIButton.h"
#include <vector>
#include "Map.h"
#include "MapView.h"

class UI:UIView {
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
	/**
	 * Render all parts of the user interface
	 * @param Map the texture which will be in the background of the map
	 * @param info the texture which will be in the background of the info
	 * @param buildings the texture which will be in the building buttons
	 */
	void Render(/*MapObjects*/);
	/**
	 * returns a pointer to the renderer
	 * @return pointer to the used renderer
	 */
	SDL_Renderer *getRenderer() const;
	/**
	 * Load an image from a link and turn it into a texture
	 * @param path path to the file containing a bitmap
	 * @return pointer to texture
	 */
	SDL_Texture * loadTexture(std::string path);
	void HandleButtons(SDL_Event &e);
private:
	/**
	 * Perform all closing action to clean the memory of the UI
	 */
	void close();
	SDL_Window *window;
	SDL_Renderer *renderer;

};

#endif