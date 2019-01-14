#include "UI.h"

using namespace std;

UI::UI(int w, int h) : UIElement(SDL_Rect{0, 0, w, h}, nullptr), state (states::inmenu) {
 	loadTexture(RenderElement::texture_lib->GetTexture(TextureLib::TextureEnum::info));
	startMenu();
    //inGame();
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

void UI::startMenu()
{
	//while (window == nullptr);
	/* ratio of UI elements
	current shape:
	__________________________
	|						 |
	|						 |
	|	menu				 |
	|						 |
	|						 |
	|						 |
	|________________________|
	|	info				 |
	|________________________|
	*/
	SDL_Rect menu_quad;
	menu_quad.x = 0;
	menu_quad.y = 0;
	menu_quad.w = quad.w;
	menu_quad.h = quad.h *8 / 10;

	StartMenu *menu_view = new StartMenu(menu_quad, this);

	addChild(menu_view);

	if (gamemanager->gameState == gamemanager->lost) {
		SDL_Rect info_quad;
		info_quad.x = 0;
		info_quad.y = quad.h * 8 / 10;
		info_quad.w = quad.w;
		info_quad.h = quad.h * 2 / 10;

		InfoView *info_view = new InfoView(info_quad, this);
		addChild(info_view);
	}
}

void UI::inGame() {
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

    children.reserve(3);
    addChild(map_view);
    addChild(building_view);
    addChild(info_view);

}



void UI::postRender() {
    SDL_RenderPresent(renderer);
	SDL_RenderClear(renderer);
	switch (gamemanager->gameState) {
	case GameManager::menu:
	case  GameManager::lost:
	case GameManager::won:
		if (state != states::inmenu) {
			state = states::inmenu;
			clearChildren();
			startMenu();
		}
		break;
	case GameManager::start:
	case GameManager::cooldown:
	case GameManager::run:
		if (state != states::ingame) {
			state = states::ingame;
			clearChildren();
			inGame();
		}
		break;
	}
}


SDL_Renderer *UI::getRenderer() const {
    return renderer;
}

