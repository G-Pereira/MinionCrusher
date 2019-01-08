/**
 * Author: Leon Klute
 * Created on: 26-11-18
 * Last Modified: 28-11-18
 */

#include <iostream>

#include "UIText.h"
#include "UI.h"

using namespace std;

UI::UI(int w, int h) : UIElement(SDL_Rect{0, 0, w, h}, nullptr) {
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
    RenderElement::renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
                                              SDL_RENDERER_PRESENTVSYNC);
    if (RenderElement::renderer == nullptr){
        throw std::runtime_error("Renderer could not be created!");
    }
    
	SDL_SetRenderDrawBlendMode(renderer, SDL_BlendMode::SDL_BLENDMODE_BLEND);

	if (TTF_Init() == -1) {
		std::cout << "TTF_Init: " << TTF_GetError();
		exit(2);
	}
    init();
}

UI::~UI() {
    //Destroy window
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    window = nullptr;
    RenderElement::renderer = nullptr;

    //Quit SDL subsystems
    SDL_Quit();
}

void UI::init() {
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

    MapView *map_view = new MapView(map_quad, this);
    BuildView *building_view = new BuildView(building_quad, this);
    InfoView *info_view = new InfoView(info_quad, this);

    map_view->loadTexture("resources/sprites/map_background.bmp");
    building_view->loadTexture("resources/sprites/right_side.bmp");
    info_view->loadTexture("resources/sprites/info.bmp");

    children.reserve(3);
    addChild(map_view);
    addChild(building_view);
    addChild(info_view);


    // add some buttons
    SDL_Rect button_quad = SDL_Rect{20, 20, 100, 100};
    UIButton *button1 = new UIButton(button_quad, building_view, MapView::setBuildTowerState);
    button1->loadTexture("resources/sprites/tower1_tile.bmp");
    building_view->addChild(button1);

    button_quad.x += 120;
	UIButton *button2 = new UIButton(button_quad, building_view, MapView::setBuildTowerState);
    button2->loadTexture("resources/sprites/tower2_tile.bmp");
    building_view->addChild(button2);

    button_quad.x -= 120;
    button_quad.y += 120;
	UIButton *button3 = new UIButton(button_quad, building_view, MapView::setBuildTowerState);
    button3->loadTexture("resources/sprites/tower3_tile.bmp");
    building_view->addChild(button3);

    SDL_Rect text_quad = SDL_Rect{30, 30, 150, 30};
    UIText *text_health = new UIText(text_quad, info_view);
	text_health->loadText2Texture("Health: 100");
    info_view->addChild(text_health);

    text_quad.y += 50;
    UIText *text_kills = new UIText(text_quad, info_view);
    text_kills->loadText2Texture("Kills:  0");
    info_view->addChild(text_kills);
}

void UI::postRender() {
    SDL_RenderPresent(renderer);
}


SDL_Renderer *UI::getRenderer() const {
    return renderer;
}

