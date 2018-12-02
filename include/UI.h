/**
 * Author: Leon Klute
 * Created on: 26-11-18
 * Last Modified: 28-11-18
 */
#pragma once
#ifndef MINIONCRUSHER_UI_H
#define MINIONCRUSHER_UI_H

#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include "MapObject.h"
#include "UIButton.h"
#include <vector>
#include "Battlefield.h"

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
	enum class viewPorts:int{
		mapview,
		infoview,
		buildingsview
	};
	void SetMap(Battlefield *);
	void AddButton(viewPorts port, SDL_Rect rect, SDL_Texture* texture);
	const SDL_Rect getMapViewport() const;
	const SDL_Rect getInfoViewport() const;
	const SDL_Rect getBuildingViewport() const;
private:
	/**
	 * Perform all closing action to clean the memory of the UI
	 */
	void close();
	Battlefield * map;
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
	std::vector<UIButton> buttons[3];
};

#endif