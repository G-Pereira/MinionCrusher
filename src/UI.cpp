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


//struct sdl_deleter
//{
//	void operator()(SDL_Window *p) const { SDL_DestroyWindow(p); }
//	void operator()(SDL_Renderer *p) const { SDL_DestroyRenderer(p); }
//	void operator()(SDL_Texture *p) const { SDL_DestroyTexture(p); }
//};

UI::UI(int w, int h, SDL_Window * wind, SDL_Renderer * rend) : UIView(SDL_Rect{0,0, w,h }, nullptr, rend) {
	window = wind;
	init();
}

UI::~UI()
{
	close();
}

void UI::init()
{
	//Initialize renderer color
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);


	/* ratio of UI elements
	current shape:
	_________________________
	|					|b	|
	|					|u	|
	|	map				|i	|
	|					|l	|
	|					|d	|
	|					|i	|
	|___________________|n	|
	|	info			|g	|
	|___________________|s__|
	*/
	SDL_Rect mapViewport;
	mapViewport.x = 0;
	mapViewport.y = 0;
	mapViewport.w = quad.w * 8 / 10;
	mapViewport.h = quad.h * 8 / 10;

	SDL_Rect buildingViewport;
	buildingViewport.x = quad.w * 8 / 10;
	buildingViewport.y = 0;
	buildingViewport.w = quad.w * 2 / 10;
	buildingViewport.h = quad.h;

	SDL_Rect infoViewport;
	infoViewport.x = 0;
	infoViewport.y = quad.h * 8 / 10;
	infoViewport.w = quad.w * 8 / 10;
	infoViewport.h = quad.h * 2 / 10;

	cout << "creating map_view" << endl;
	MapView * map_view = new MapView(mapViewport, this);
	cout << "creating building_view" << endl;
	BuildView * building_view = new BuildView(buildingViewport, this);
	cout << "creating info_view" << endl;
	UIView * info_view = new UIView(infoViewport, this);

	map_view->loadTexture("resources/sprites/map_background.bmp");
	building_view->loadTexture("resources/sprites/right_side.bmp");
	info_view->loadTexture("resources/sprites/info.bmp");

	children.push_back(map_view);
	children.push_back(building_view);
	children.push_back(info_view);


	// add some buttons
	SDL_Rect quad = SDL_Rect{20,20, 100,100};
	BuildButton *button = new BuildButton(quad, nullptr, building_view);
	button->loadTexture("resources/sprites/tower1_tile.bmp");
	building_view->addChild(button);

}
void UI::close()
{
	////Free loaded images
	//SDL_DestroyTexture(map_texture);
	//map_texture = nullptr;
	//SDL_DestroyTexture(info_texture);
	//info_texture = nullptr;
	//SDL_DestroyTexture(buildings_texture);
	//buildings_texture = nullptr;

	//Destroy window	
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	window = nullptr;
	renderer = nullptr;

	//Quit SDL subsystems
	//IMG_Quit();
	SDL_Quit();
}

void UI::postRender(/*MapObjects*/) {
	
	SDL_RenderPresent(renderer);
}
void UI::preRender()
{
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

void UI::setMap(Map *new_map)
{
	((MapView*)children[0])->setMap(new_map);// this is not very nice
}
