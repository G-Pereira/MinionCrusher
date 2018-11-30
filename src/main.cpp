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
Uint32 gameUpdate(Uint32 interval, void *param /*param, MAPOBJECTSclass*/)
{
	cout << "Test" << endl;
	// For each minion: Check current position
	// For each tower: Check if it can fire by checking its ticks.
		// If yes: Find closest minion. If in range: damage it. Set ticks back to firing period.
		// If no: reduce tower ticks by one.
	return interval;
}



int main(int argc, char* args[]) {

	// INITIALIZE THE TIMER FUNCTION OF SDL
	if (SDL_Init(SDL_INIT_TIMER) != 0) {
		cout << "SDL could not initialize timers" << endl;
	}
	// INITIALIZE THE CALLBACK TIMER
	if (SDL_TimerID timer_id = SDL_AddTimer(1000, gameUpdate, static_cast<void *>(nullptr)) == 0) {
		cout << "SDL was unable to create a timer. " << endl;
	}

	// LOAD BLUEPRINT FROM FILE
	Blueprint blueprint("configs/simple.blueprint");
	// CREATE MAP FROM BLUEPRINT
	Map map(blueprint);

	// INITIALIZE THE USER INTERFACE
	ui.init();

	// add some buttons
	SDL_Texture * temptextu = ui.loadTexture("resources/tower1_tile.bmp");

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
