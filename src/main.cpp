#include <iostream>
#include <SDL.h>
#undef main

#include "UI.h"

using namespace std;

/**
// Updates position of all mapobjects in the game on a fixed interval. This includes all towers, minions etc.
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



int main(int arg, char* arr[]) {

	// INITIALIZE THE TIMER FUNCTION OF SDL
	if (SDL_Init(SDL_INIT_TIMER) != 0) {							
		cout << "SDL could not initialize timers" << endl;
	}
	// INITIALIZE THE CALLBACK TIMER
	if (SDL_TimerID timer_id = SDL_AddTimer(1000, gameUpdate, static_cast<void *>(nullptr)) == 0) {
		cout << "SDL was unable to create a timer. " << endl;
	}
	// INITIALIZE THE USER INTERFACE
	UI ui;

	// MAKE SURE THE PROGRAM DOESN'T EXIT
	while (1);

	return 0;
}