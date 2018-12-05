/**
 * Author: Leon Klute
 * Created on: 26-11-18
 * Last Modified: 28-11-18
 */

#include <iostream>
#include "UI.h"

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

UI::~UI() {
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
	SDL_Rect map_quad;
	map_quad.x = 0;
	map_quad.y = 0;
	map_quad.w = quad.w * 8 / 10;
	map_quad.h = quad.h * 8 / 10;

	SDL_Rect building_quad;
	building_quad.x = quad.w * 8 / 10;
	building_quad.y = 0;
	building_quad.w = quad.w * 2 / 10;
	building_quad.h = quad.h;

	SDL_Rect info_quad;
	info_quad.x = 0;
	info_quad.y = quad.h * 8 / 10;
	info_quad.w = quad.w * 8 / 10;
	info_quad.h = quad.h * 2 / 10;

	cout << "creating map_view" << endl;
	MapView * map_view = new MapView(map_quad, this);
	cout << "creating building_view" << endl;
	BuildView * building_view = new BuildView(building_quad, this);
	cout << "creating info_view" << endl;
	UIView * info_view = new UIView(info_quad, this);

	map_view->loadTexture("resources/sprites/map_background.bmp");
	building_view->loadTexture("resources/sprites/right_side.bmp");
	info_view->loadTexture("resources/sprites/info.bmp");

	children.push_back(map_view);
	children.push_back(building_view);
	children.push_back(info_view);


	// add some buttons
	SDL_Rect button_quad = SDL_Rect{20,20, 100,100};
	BuildButton *button = new BuildButton(button_quad, nullptr, building_view);
	button->loadTexture("resources/sprites/tower1_tile.bmp");
	building_view->addChild(button);

}

void UI::close() {
    //Destroy window
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    window = nullptr;
    renderer = nullptr;

    //Quit SDL subsystems
    //IMG_Quit();
    SDL_Quit();
}

void UI::postRender() {
	
	SDL_RenderPresent(renderer);
}
void UI::preRender()
{
}


SDL_Renderer * UI::getRenderer() const {
	return renderer;
}

void UI::setMap(Map *new_map)
{
	((MapView*)children[0])->setMap(new_map);// this is not very nice
}
