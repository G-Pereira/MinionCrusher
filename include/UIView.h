#pragma once
#ifndef MINIONCRUSHER_UIVIEW_H
#define MINIONCRUSHER_UIVIEW_H

#include <SDL.h>
#include <string>
#include <vector>
#include "MapObject.h"
#include "UIButton.h"
#include <vector>
#include "Map.h"


class UIView {
public:
	/**
	 * Constructor
	 * @param w width in pixels
	 * @param h height in pixels
	 */
	UIView(int x, int y, int w, int h);
	UIView(int w, int h);
	UIView(SDL_Rect);
	/**
	 * Destructor of the UI, calls the UI close method
	 */
	~UIView();
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
	virtual void Render();
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
	void loadTexture(std::string path);

	void setQuad(SDL_Rect);
	void addChild(UIView * new_child);
	std::vector<UIView*> getChildren();

	virtual void HandleEvents(SDL_Event &e);

	void close();

	SDL_Texture * background;
	SDL_Renderer * renderer;
	SDL_Rect quad;
	std::vector<UIView*> children;
};






#endif
