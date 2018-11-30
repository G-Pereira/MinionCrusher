#include <iostream>
#include <Blueprint.h>
#include <Map.h>
#include <SDL.h>
#include <string>
#include <stdint.h>
#include "../include/UI.h"
using namespace std;

UI ui = UI(1280, 720);

/**
* Updates position of all mapobjects in the game on a fixed interval. This includes all towers, minions etc.
*/
Uint32 gameUpdate(Uint32 interval, void * /*param, MAPOBJECTSclass*/) {
    // Update all minion positions

    // For each tower: Check if it can fire by checking its ticks.
    // If yes: Find closest minion and damage it. Set ticks back to firing period.
    // If no: reduce tower ticks by one.
    return interval;
}

    Blueprint blueprint("configs/simple.blueprint");
    Map map(blueprint);
int main(int argc, char* args[]) {
	cout << "Hi" << endl;
	ui.init();



	SDL_TimerID timer_id = SDL_AddTimer(100, gameUpdate, static_cast<void *>(nullptr));

	SDL_Texture * temptextu = ui.loadTexture("resources/tower1_tile.bmp");

	// add some buttons
	ui.AddButton(UI::viewPorts::buildingsview, SDL_Rect{ 50,50,50,50 }, temptextu);

	ui.AddButton(UI::viewPorts::buildingsview, SDL_Rect{ 200,50,50,50 }, temptextu);

	ui.AddButton(UI::viewPorts::buildingsview, SDL_Rect{ 50,200,50,50 }, temptextu);

	ui.AddButton(UI::viewPorts::buildingsview, SDL_Rect{ 200,200,50,50 }, temptextu);


	bool quit = false;
	while (!quit) {
		//update screen
		ui.Render(/*MapObjects*/);
		SDL_Event e;
		while (SDL_PollEvent(&e) != 0)
		{
			//User requests quit
			if (e.type == SDL_QUIT)
			{
				cout << "quitting" << endl;
				quit = true;

			}

			//Handle button events
			ui.HandleButtons(e);
		}
	}
	return 0;
}