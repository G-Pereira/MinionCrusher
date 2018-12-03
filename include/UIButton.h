#pragma once
#include <SDL.h>

class UIButton
{
public:
	//Initializes internal variables
	//UIButton();
	/**
	* @param: renderer Rectangle that defines the size and position
	* @param: current Texture to start off with, if left to zero will be same as param off
	* @param: mouse_on Texture to show when mouse is on the button
	* @param: mouse_off Texture to show when user is not interacting with the button
	* @param: button_pressed Texture to show after user has clicked this button
	* @param: funct call back function to call when button is clicked
	*/
	UIButton(SDL_Rect renderer, SDL_Texture *current, SDL_Texture *mouse_on, SDL_Texture *mouse_off, SDL_Texture *button_pressed, void funct(UIButton & self, SDL_Event &));

	~UIButton();
	/**
	*Sets the postion of the this button
	*/
	void setPosition(int x, int y);
	/**
	* Sets the size of the this button
	*/
	void setSize(int x, int y);

	/**
	*Should be called on SDL_event to handel them
	*/
	void handleEvent(SDL_Event* e);

	/*
	*defines the shape and position of this button
	*/
	SDL_Rect rect;
	void render(SDL_Renderer * renderer);
	SDL_Texture * current;
	SDL_Texture * mouse_on;
	SDL_Texture * mouse_off;
	SDL_Texture * button_pressed;

private:
	/**
	* pointer to callback function
	*/
	void (*eventhandler)(UIButton& self, SDL_Event &e);

};

