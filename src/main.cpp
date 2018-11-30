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

void BuildingButtonhandleEvent(UIButton &self, SDL_Event &e);

int main(int argc, char* args[]) {
    //Blueprint blueprint("configs/simple.blueprint");
    //Map map(blueprint);
	cout << "Hi" << endl;
	ui.init();


	SDL_TimerID timer_id = SDL_AddTimer(100, gameUpdate, static_cast<void *>(nullptr));

	// add some buttons
	SDL_Texture * temptextu = ui.loadTexture("resources/tower1_tile.bmp");

	ui.AddButton(UI::viewPorts::buildingsview, SDL_Rect{ 50,50,50,50 }, temptextu, BuildingButtonhandleEvent);
	ui.AddButton(UI::viewPorts::buildingsview, SDL_Rect{ 200,50,50,50 }, temptextu, BuildingButtonhandleEvent);
	ui.AddButton(UI::viewPorts::buildingsview, SDL_Rect{ 50,200,50,50 }, temptextu, BuildingButtonhandleEvent);
	ui.AddButton(UI::viewPorts::buildingsview, SDL_Rect{ 200,200,50,50 }, temptextu, BuildingButtonhandleEvent);

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
				cout << "SDL_MOUSEMOTION" << endl;
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