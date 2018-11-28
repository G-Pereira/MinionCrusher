#include <iostream>
#include <SDL.h>
#include <string>

#include "../include/UI.h"
using namespace std;

SDL_Texture * map;
SDL_Texture * info;
SDL_Texture * buildings;
UI ui = UI(1280, 720);

Uint32 gameUpdate(Uint32 interval, void * /*param*/)
{
	//Update screen
	ui.Render(map, info, buildings);
	//SDL_RenderPresent(gRenderer);

	cout << "Test" << endl;
	return interval;
}

int main(int argc, char* args[]) {
	cout << "Hi" << endl;
	ui.init();

	map = ui.loadTexture("resources/map.bmp");
	info = ui.loadTexture("resources/info.bmp");
	buildings = ui.loadTexture("resources/right_side.bmp");


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