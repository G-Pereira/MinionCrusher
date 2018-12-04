#include <iostream>
#include <Map.h>
#include <string>
#include <stdint.h>
#include <list>
#include "UIView.h"
#include "UI.h"
#include "types.h"

using namespace std;

constexpr int WINDOW_HEIGHT = 720;
constexpr int WINDOW_WIDTH = 1280;

// Temporary location of minion spawn information
CartesianCoordinates spawnLocation = { 0, 1 };
int ticksToNextMinion = 3;
int tickCount = 2;

/**
* Updates position of all mapobjects in the game on a fixed interval. This includes all towers, minions etc.
*/
Uint32 gameUpdate(Uint32 interval , void *m)
{
	Map *map = reinterpret_cast<Map *>(m);


	// Move all minions in the right direction
	bool finished;
	do {
		finished = true;
		for (Minion &minion : (map->minions)) {

			int dir = (int)map->path[minion.moveCount].getType();
			minion.setCoordinates(
				{ minion.getCoordinates().x + -(dir == 1) + (dir == 4),
				 minion.getCoordinates().y + -(dir == 3) + (dir == 2) }
			);
			if (minion.moveCount == (int)map->path.size() - 1) {
				map->minions.pop_front();
				finished = false;
				break;
			}
			minion.moveCount = minion.moveCount + 1;

			//cout << "moveCount: " << minion.moveCount << " Direction: " << dir << endl;
		}
	} while (!finished);
	// Add minions to the battlefield on an interval
	if (tickCount >= ticksToNextMinion) {
		tickCount = 0;
		Minion minion = Minion(spawnLocation.x, spawnLocation.y, 1, 1, 100, 1, 1);
		map->minions.push_back(minion);
	}
	else {
		tickCount++;
	}

	// For each tower: Check if it can fire by checking its ticks.
		// If yes: Find closest minion. If in range: damage it. Set ticks back to firing period.
		// If no: reduce tower ticks by one.
	return interval;
}



int main(int argc, char * args[]){
	if (argc > 1) {
		cout << "too many arguments: ";
		for (int i = 0; i < argc; i++) {
			cout << args[i] << " ";
		}
	}

	// CREATE MAP FROM BLUEPRINT
	Map map("resources/blueprints/simple.blueprint");

	// INITIALIZE THE TIMER FUNCTION OF SDL
	if (SDL_Init(SDL_INIT_TIMER) != 0) {
		cout << "SDL could not initialize timers" << endl;
	}
	// INITIALIZE THE CALLBACK TIMER
	SDL_TimerID timer_id = SDL_AddTimer(1000, gameUpdate, &map);
	if (timer_id == 0) {
		cout << "SDL was unable to create a timer. " << endl;
	}

	// INITIALIZE THE USER INTERFACE

	// Init SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		throw std::runtime_error("SDL could not initialize!");

	//Set texture filtering to linear
	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		throw std::runtime_error("Warning: Linear texture filtering not enabled!");

	// Create a Window in the middle of the screen
	SDL_Window * window = SDL_CreateWindow("MinionCrusher", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, 
		WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == nullptr)
		throw std::runtime_error("Window could not be created!");

	// Create a new renderer
	SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
		SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr)
		throw std::runtime_error("Renderer could not be created!");
	else
		cout << "initialize renderer at address:" << renderer << endl;
	UI ui = UI(1280, 720, window, renderer);
    try {
        ui.init();
    } catch (std::exception& e){
        std::cout << e.what();
    }
	ui.setMap(&map);




	bool quit = false;
	while (!quit) {
		//update screen
		ui.Render(/*MapObjects*/);
		SDL_Event e;
		while (SDL_PollEvent(&e) != 0)
		{
			//Handle button events
			ui.HandleEvents(e);
			//User requests quit
			if (e.type == SDL_QUIT)
			{
				cout << "quitting" << endl;
				quit = true;

			}

		}
	}

	return 0;
}

