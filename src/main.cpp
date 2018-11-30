#include <iostream>
#include <Blueprint.h>
#include <Map.h>

#undef main

#include "UI.h"

using namespace std;

/**
// Updates position of all mapobjects in the game on a fixed interval. This includes all towers, minions etc.
*/
Uint32 gameUpdate(Uint32 interval, void * /*param, MAPOBJECTSclass*/)
{
	// Update all minion positions

	// For each tower: Check if it can fire by checking its ticks.
		// If yes: Find closest minion and damage it. Set ticks back to firing period.
		// If no: reduce tower ticks by one.
	return interval;
}

int main() {
	cout << "Hi" << endl;
	Blueprint blueprint("configs/simple.blueprint");
	Map map(blueprint);
	UI ui;
	int hoi;
	cin >> hoi;
	return 0;
}