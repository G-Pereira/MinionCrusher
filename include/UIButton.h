/**
 * Author: Leon Klute
 * Created on: 04-12-18
 * Last Modified: 04-12-18
 */

#pragma once
#include "UIView.h"
#include <SDL.h>

class UIButton: public UIView
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
	UIButton(SDL_Rect , void funct(UIButton & self, SDL_Event &), UIView * parent);

	~UIButton();

	/**
	*Should be called on SDL_event to handel them
	*/
	virtual void handleEvents(SDL_Event* e);
	
protected:
	/**
	* pointer to callback function
	*/
	void (*eventhandler)(UIButton& self, SDL_Event &e);

};

