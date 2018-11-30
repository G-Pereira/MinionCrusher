/**
 * Author: Leon Klute
 * Created on: 26-11-18
 * Last Modified: 28-11-18
 */
#pragma once

#include <SDL.h>
#include <string>
#include <vector>
#include "MapObject.h"
#include "UIButton.h"
#include <vector>

class tempMap {
public:
	int getXTiles() {
		return x_tiles;
	}
	int getYTiles() {
		return y_tiles;
	}
private:
	int x_tiles;
	int y_tiles;
};
class UI {
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
	bool init();
	/**
	 * Render all parts of the user interface
	 * @param Map the texture which will be in the background of the map
	 * @param info the texture which will be in the background of the info
	 * @param buildings the texture which will be in the building buttons
	 */
	void Render(/*MapObjects*/);
	/**
	 * Load an image from a link and turn it into a texture
	 * @param path path to the file containing a bitmap
	 * @return pointer to texture
	 */
	void RenderMap(std::vector<MapObject*> map_objects);
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
	static enum viewPorts:int{
		mapview,
		infoview,
		buildingsview
	};
	void AddButton(enum viewPorts port, SDL_Rect rect, SDL_Texture* texture);
private:
	/**
	 * Perform all closing action to clean the memory of the UI
	 */
	void close();

	SDL_Texture * map_texture;
	SDL_Texture * info_texture;
	SDL_Texture * buildings_texture;
	SDL_Window *window;
	SDL_Renderer *renderer;
	int width;
	int height;
	SDL_Rect mapViewport;
	SDL_Rect infoViewport;
	SDL_Rect buildingViewport;
	tempMap * map;
	std::vector<UIButton> buttons[3];
};