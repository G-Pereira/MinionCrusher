#include <iostream>
#include <SDL.h>
#include <string>
#include <stdint.h>
#include "../include/UI.h"
using namespace std;

UI ui = UI(1280, 720);

/**
* Updates position of all mapobjects in the game on a fixed interval. This includes all towers, minions etc.
*/
Uint32 gameUpdate(Uint32 interval, void * /*param, MAPOBJECTSclass*/)
{
	//Update screen
	ui.Render();
	//SDL_RenderPresent(gRenderer);

	cout << "Test" << endl;
	// Update all minion positions

	// For each tower: Check if it can fire by checking its ticks.
		// If yes: Find closest minion and damage it. Set ticks back to firing period.
		// If no: reduce tower ticks by one.
	return interval;
}

int main(int argc, char* args[]) {
	cout << "Hi" << endl;
	ui.init();



	SDL_TimerID timer_id = SDL_AddTimer(100, gameUpdate, static_cast<void *>(nullptr));

	bool quit = false;
	while (!quit) {
		//ui.Render(map, info, buildings);
		SDL_Event e;
		while (SDL_PollEvent(&e) != 0)
		{
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