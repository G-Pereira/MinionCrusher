/*! \mainpage Minion Crusher
 * Minion Crusher is a tower defense game where the player builds and upgrades towers to defend his base from the enemy minions.
 *
 */

#include <iostream>

#include "Map.h"
#include "UI.h"
#include "gameManager.h"

using namespace std;

constexpr int WINDOW_HEIGHT = 720;
constexpr int WINDOW_WIDTH = 1280;
constexpr Uint32 UPDATE_FREQUENCY = 300;
constexpr Uint32 UPDATE_PERIOD = 1000 / UPDATE_FREQUENCY;

// Temporary location of minion spawn information

void UIInit(SDL_Window *&window, SDL_Renderer *&renderer);

GameManager gameManager;

/**
* Updates position of all mapobjects in the game on a fixed interval. This includes all towers, minions etc.
*/
Uint32 gameUpdate(Uint32 interval, void *m) {
    Map *map = reinterpret_cast<Map *>(m);
    std::lock_guard<std::mutex> lock(map->getMutex());
	gameManager.update();
    return interval;
}


int main(int argc, char *args[]) {
    if (argc > 1) {
        cout << "too many arguments: ";
        for (int i = 0; i < argc; i++) {
            cout << args[i] << " ";
        }
    }

    // CREATE MAP FROM BLUEPRINT
    Map map("resources/blueprints/1.blueprint");
    map.towers.push_back(Tower(2, 2, 1, 1, 25, 3, 10, AmmoType{}));
	gameManager.map = &map;

    // INITIALIZE THE USER INTERFACE
    SDL_Window *window;
    SDL_Renderer *renderer;
    try {
        UIInit(window, renderer);
    }
    catch (std::exception &e) {
        std::cout << e.what();
    }
    UI ui = UI(WINDOW_WIDTH, WINDOW_HEIGHT, window, renderer);
    //Initialize the map
    ui.setMap(&map);

    // INITIALIZE THE CALLBACK TIMER
    SDL_TimerID timer_id = SDL_AddTimer(UPDATE_PERIOD, gameUpdate, &map);
    if (timer_id == 0) {
        cout << "SDL was unable to create a timer. " << endl;
    }

    bool quit = false;
    while (!quit) {
        //update screen
        ui.Render();
        SDL_Event e;
        while (SDL_PollEvent(&e) != 0) {
            //Handle button events
            ui.HandleEvents(e);
            //User requests quit
            if (e.type == SDL_QUIT) {
                cout << "quitting" << endl;
                quit = true;

            }
        }
    }
    return 0;
}

void UIInit(SDL_Window *&window, SDL_Renderer *&renderer) {
    // INITIALIZE THE USER INTERFACE

// Init SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
        throw std::runtime_error("SDL could not initialize!");

    //Set texture filtering to linear
    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
        throw std::runtime_error("Warning: Linear texture filtering not enabled!");

    // Create a Window in the middle of the screen
    window = SDL_CreateWindow("MinionCrusher", SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH,
                              WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr)
        throw std::runtime_error("Window could not be created!");

    // Create a new renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
                                              SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr)
        throw std::runtime_error("Renderer could not be created!");
}


