/**
 * Author: Leon Klute
 * Created on: 04-12-18
 * Last Modified: 04-12-18
 */

#pragma once

#include "UIElement.h"

class UIButton : public UIElement {
public:
    //Initializes internal variables
    //UIButton();
    /**
    * @param: quad that defines position and size of the element on screen
    * @param: funct call back function to call when button is clicked
    * @param: parent pointer to the element that contains this element
    */
    UIButton(SDL_Rect quad, UIElement *parent, ButtonTypes button);

    ~UIButton();

	static int mouseClick(void * userdata, SDL_Event * e);

protected:
    //void (*eventhandler)(UIButton &self, SDL_Event &e);
	ButtonTypes button_type;


};

