#pragma once
#include <SDL.h>

class UI {
public:
	UI();
	//~UI();



private:
	void init();
	SDL_Window *window;
	SDL_Renderer *renderer;

};