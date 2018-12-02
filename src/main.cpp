#include <iostream>
#include <Blueprint.h>
#include <Battlefield.h>
#include <SDL.h>
#include <string>
#include <stdint.h>
#include "UI.h"
using namespace std;

UI ui = UI(1280, 720);

/**
* Updates position of all mapobjects in the game on a fixed interval. This includes all towers, minions etc.
*/
Uint32 gameUpdate(Uint32 interval , void* param = 0/*, MAPOBJECTSclass*/)
{
	// param is printed here to not trigger the -Werror unused parameter
	cout << "Test" <<  param << endl;
	// For each minion: Check current position
	// For each tower: Check if it can fire by checking its ticks.
		// If yes: Find closest minion. If in range: damage it. Set ticks back to firing period.
		// If no: reduce tower ticks by one.
	return interval;
}

void BuildingButtonhandleEvent(UIButton &self, SDL_Event &e);

int main(){

	// INITIALIZE THE TIMER FUNCTION OF SDL
	if (SDL_Init(SDL_INIT_TIMER) != 0) {
		cout << "SDL could not initialize timers" << endl;
	}
	// INITIALIZE THE CALLBACK TIMER
    SDL_TimerID timer_id = SDL_AddTimer(1000, gameUpdate, static_cast<void *>(nullptr));
	if (timer_id == 0) {
		cout << "SDL was unable to create a timer. " << endl;
	}

	// LOAD BLUEPRINT FROM FILE
	Blueprint blueprint("resources/blueprints/simple.blueprint");
	// CREATE MAP FROM BLUEPRINT
	Battlefield map(&blueprint);

	// INITIALIZE THE USER INTERFACE
	ui.init();

	// add some buttons
	SDL_Texture * temptextu = ui.loadTexture("resources/sprites/tower1_tile.bmp");

	ui.AddButton(UI::viewPorts::buildingsview, SDL_Rect{ 20,20,100,100 }, temptextu);
	ui.AddButton(UI::viewPorts::buildingsview, SDL_Rect{ 140,20,100,100 }, temptextu);
	ui.AddButton(UI::viewPorts::buildingsview, SDL_Rect{ 20,140,100,100 }, temptextu);
	ui.AddButton(UI::viewPorts::buildingsview, SDL_Rect{ 140,140,100,100 }, temptextu);



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


void BuildingButtonhandleEvent(UIButton &self, SDL_Event &e)
{
	//If mouse event happened
	if (e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP)
	{
		//Get mouse position
		int x, y;
		SDL_GetMouseState(&x, &y);
		// add the offset of the viewport
		x -= ui.getBuildingViewport().x;
		y -= ui.getBuildingViewport().y;
		//Check if mouse is in button
		bool inside = true;

		//Mouse is left of the button
		if (x < self.rect.x)
		{
			inside = false;
		}
		//Mouse is right of the button
		else if (x > self.rect.x + self.rect.w)
		{
			inside = false;
		}
		//Mouse above the button
		else if (y < self.rect.y)
		{
			inside = false;
		}
		//Mouse below the button
		else if (y > self.rect.y + self.rect.h)
		{
			inside = false;
		}

		//Mouse is outside button
		if (!inside)
		{
			self.current = self.mouse_off;
		}
		//Mouse is inside button
		else
		{
			//Set mouse over sprite
			switch (e.type)
			{
			case SDL_MOUSEMOTION:
				//cout << "SDL_MOUSEMOTION" << endl;
				self.current = self.mouse_on;
				break;

			case SDL_MOUSEBUTTONDOWN:
				cout << "SDL_MOUSEBUTTONDOWN" << endl;
				self.current = self.pressed;
				break;

			case SDL_MOUSEBUTTONUP:
				cout << "SDL_MOUSEBUTTONUP" << endl;
				self.current = self.pressed;
				break;
			}
		}
	}
}