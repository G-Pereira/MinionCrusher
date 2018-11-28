/**
 * Author: Leon Klute
 * Created on: 26-11-18
 * Last Modified: 28-11-18
 */

#include <iostream>
#include "UI.h"
#include "types.h"
#include "MapObject.h"

using namespace std;

UI::UI(int w, int h): width(w), height(h){
	window = nullptr;
	renderer = nullptr;
	map_texture = nullptr;
	buildings_texture = nullptr;
	info_texture = nullptr;
	buildingViewport = SDL_Rect();
	infoViewport = SDL_Rect();
	mapViewport = SDL_Rect();
}

UI::~UI()
{
	close();
}

bool UI::init()
{
	// Init SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		return false;
	}

	//Set texture filtering to linear
	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
	{
		printf("Warning: Linear texture filtering not enabled!");
	}

	// Create a Window in the middle of the screen
	window = SDL_CreateWindow("MinionCrusher", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, width,
		height, SDL_WINDOW_SHOWN);
	if (window == nullptr) {
		printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
		return false;
	}
	// Create a new renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
		SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr)
	{
		printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
		return false;
	}
	//Initialize renderer color
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);


	/* ratio of UI elements
	_________________
	|			|b	|
	|			|u	|
	|	map		|i	|
	|			|l	|
	|			|d	|
	|			|i	|
	|___________|n	|
	|	info	|g	|
	|___________|s__|
	*/
	mapViewport.x = 0;
	mapViewport.y = 0;
	mapViewport.w = width * 8 / 10;
	mapViewport.h = height * 8 / 10;

	buildingViewport.x = width * 8 / 10;
	buildingViewport.y = 0;
	buildingViewport.w = width * 2 / 10;
	buildingViewport.h = height;

	infoViewport.x = 0;
	infoViewport.y = height * 8 / 10;
	infoViewport.w = width * 8 / 10;
	infoViewport.h = height * 2 / 10;

	map_texture = loadTexture("resources/map.bmp");
	info_texture = loadTexture("resources/info.bmp");
	buildings_texture = loadTexture("resources/right_side.bmp");

	return true;
}

void UI::close()
{
	//Free loaded images
	SDL_DestroyTexture(map_texture);
	map_texture = nullptr;
	SDL_DestroyTexture(info_texture);
	info_texture = nullptr;
	SDL_DestroyTexture(buildings_texture);
	buildings_texture = nullptr;

	//Destroy window	
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	window = nullptr;
	renderer = nullptr;

	//Quit SDL subsystems
	//IMG_Quit();
	SDL_Quit();
}

void UI::Render() {
	static CartesianCoordinates pos = CartesianCoordinates{ 0, 0 };
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(renderer);
	pos.x++;
	pos.y++;

	MapObject map_object = MapObject(pos, ObjectSize{ 100, 100 });
	std::vector<MapObject*> map_objects = std::vector<MapObject*>();
	map_objects.push_back(&map_object);
	RenderMap(map_texture, map_objects);

	//Top right viewport
	SDL_RenderSetViewport(renderer, &buildingViewport);

	//Render texture to screen
	SDL_RenderCopy(renderer, buildings_texture, nullptr, nullptr);


	//Bottom viewport
	SDL_RenderSetViewport(renderer, &infoViewport);


	//Render texture to screen
	SDL_RenderCopy(renderer, info_texture, nullptr, nullptr);


	//Update screen
	SDL_RenderPresent(renderer);
}

void UI::RenderMap(SDL_Texture* Map, std::vector<MapObject*> map_objects/*, mapclass map */ ) {
	//Top left corner viewport
	SDL_RenderSetViewport(renderer, &mapViewport);

	//Render texture to screen
	SDL_RenderCopy(renderer, Map, nullptr, nullptr);
	for (auto mo  : map_objects) {
		auto coordinates = mo->getCoordinates();
		auto dims = mo->getDimensions();
		SDL_Rect fillRect = { coordinates.x, coordinates.y,  dims.height, dims.width};

		SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
		SDL_RenderFillRect(renderer, &fillRect);
	}

}

SDL_Renderer * UI::getRenderer() const {
	return renderer;
}

SDL_Texture* UI::loadTexture(std::string path)
{
	//The final texture
	SDL_Texture* newTexture = nullptr;

	//Load image at specified path
	SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
	if (loadedSurface == nullptr)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), SDL_GetError());
	}
	else
	{
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture == nullptr)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return newTexture;
}