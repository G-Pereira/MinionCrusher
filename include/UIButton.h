#pragma once
#include <SDL.h>

class UIButton
{
public:
	//Initializes internal variables
	//UIButton();
	//Initializes internal variables
	UIButton(SDL_Rect r, SDL_Texture *c, SDL_Texture *on, SDL_Texture *off, SDL_Texture *button_pressed);

	~UIButton();
	//Sets top left position
	void setPosition(int x, int y);
	//Sets the size
	void setSize(int x, int y);

	//Handles mouse event
	void handleEvent(SDL_Event* e);

	//Shows button sprite
	void render(SDL_Renderer * renderer);

private:
	//Top left position
	SDL_Rect rect;
	
	//Currently used global sprite
	SDL_Texture * current;
	SDL_Texture * mouse_on;
	SDL_Texture * mouse_off;
	SDL_Texture * pressed;
};

