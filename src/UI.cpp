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

UI::UI(int w, int h) : UIElement(SDL_Rect{0,0, w,h }, nullptr){
	// Init SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		throw std::runtime_error("SDL could not initialize!");

	//Set texture filtering to linear
	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		throw std::runtime_error("Warning: Linear texture filtering not enabled!");

	// Create a Window in the middle of the screen
	window = SDL_CreateWindow("MinionCrusher", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, quad.w,
		quad.h, SDL_WINDOW_SHOWN);
	if (window == nullptr)
		throw std::runtime_error("Window could not be created!");

	// Create a new renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
		SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr)
		throw std::runtime_error("Renderer could not be created!");
	init();
}

UI::~UI() {
	//Destroy window
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	window = nullptr;
	renderer = nullptr;

	//Quit SDL subsystems
	//IMG_Quit();
	SDL_Quit();
}

void UI::init()
{
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

	MapView * map_view = new MapView(map_quad, this);
	BuildView * building_view = new BuildView(building_quad, this);
	UIElement * info_view = new UIElement(info_quad, this);

	map_view->loadTexture(renderer, "resources/sprites/map_background.bmp");
	building_view->loadTexture(renderer, "resources/sprites/right_side.bmp");
	info_view->loadTexture(renderer, "resources/sprites/info.bmp");

	children.reserve(3);
	addChild(map_view);
	addChild(building_view);
	addChild(info_view);


	// add some buttons
	SDL_Rect button_quad = SDL_Rect{ 20,20, 100,100 };
	BuildButton *button1 = new BuildButton(button_quad, nullptr, building_view);
	button1->loadTexture(renderer, "resources/sprites/tower1_tile.bmp");
	building_view->addChild(button1);

	button_quad.x += 120;
	BuildButton *button2 = new BuildButton(button_quad, nullptr, building_view);
	button2->loadTexture(renderer, "resources/sprites/tower2_tile.bmp");
	building_view->addChild(button2);

	button_quad.x -= 120;
	button_quad.y += 120;
	BuildButton *button3 = new BuildButton(button_quad, nullptr, building_view);
	button3->loadTexture(renderer, "resources/sprites/tower3_tile.bmp");
	building_view->addChild(button3);

}

void UI::postRender(SDL_Renderer * renderer) {
	
	SDL_RenderPresent(renderer);
}


SDL_Renderer * UI::getRenderer() const {
	return renderer;
}

void UI::setMap(Map *new_map)
{
	((MapView*)children[(int)elements::map])->setMap(renderer, new_map);// this is not very nice
}
