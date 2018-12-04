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
#include "BuildButton.h"
#include "BuildView.h"

class UI:public UIView {
public:
	/**
	 * Constructor
	 * @param w width in pixels
	 * @param h height in pixels
	 */
	UI(int w, int h, SDL_Window * wind, SDL_Renderer * rend);
	/**
	 * Destructor of the UI, calls the UI close method
	 */
	~UI();
	/**
	 * Initilialize the UI
	 */
	void init();

	void postRender();
	void preRender();
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

	void setMap(Map *);

private:
	/**
	 * Perform all closing action to clean the memory of the UI
	 */
	void close();
	SDL_Window *window;

};

#endif