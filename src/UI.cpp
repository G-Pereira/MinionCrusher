#include <iostream>
#include "UI.h"

UI::UI()
{
	this->init();
}

UI::~UI()
{
}

void UI::init()
{
	// Init SDL
	SDL_Init(SDL_INIT_EVERYTHING);

	// Create a Window in the middle of the screen
	window = SDL_CreateWindow("MinionCrusher", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, 1000,
		600, SDL_WINDOW_SHOWN);

	// Create a new renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
		SDL_RENDERER_PRESENTVSYNC);
}