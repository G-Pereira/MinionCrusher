#include "UI.h"
#include <SDL.h>
#include <iostream>


UI::UI(int w, int h): width(w), height(h){
	window = NULL;
	renderer = NULL;
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
	if (window == NULL) {
		printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
		return false;
	}
	// Create a new renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
		SDL_RENDERER_PRESENTVSYNC);
	if (renderer == NULL)
	{
		printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
		return false;
	}
	//Initialize renderer color
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);


	
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

	return true;
}
void UI::close()
{
	//Free loaded image
	//SDL_DestroyTexture(texture);
	//gTexture = NULL;

	//Destroy window	
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	window = NULL;
	renderer = NULL;

	//Quit SDL subsystems
	//IMG_Quit();
	SDL_Quit();
}

void UI::Render(SDL_Texture* Map, SDL_Texture* info, SDL_Texture* buildings) {
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(renderer);
	Position pos = Position(100.0F, 100.0F);
	MapObject map_object = MapObject(pos);
	std::vector<MapObject*> map_objects = std::vector<MapObject*>();
	RenderMap(Map, map_objects);

	//Top right viewport
	SDL_RenderSetViewport(renderer, &buildingViewport);

	//Render texture to screen
	SDL_RenderCopy(renderer, buildings, NULL, NULL);


	//Bottom viewport
	SDL_RenderSetViewport(renderer, &infoViewport);


	//Render texture to screen
	SDL_RenderCopy(renderer, info, NULL, NULL);


	//Update screen
	SDL_RenderPresent(renderer);
}

void UI::RenderMap(SDL_Texture* Map, std::vector<MapObject*> map_objects) {
	//Top left corner viewport
	SDL_RenderSetViewport(renderer, &mapViewport);

	//Render texture to screen
	SDL_RenderCopy(renderer, Map, NULL, NULL);
	for (auto mo  : map_objects) {
		SDL_Rect fillRect = { mo->pos.x, mo->pos.y,  100, 100 };
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
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), SDL_GetError());
	}
	else
	{
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return newTexture;
}