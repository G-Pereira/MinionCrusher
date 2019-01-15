#pragma once

#include "UIElement.h"

/**
 * UIButton is a UIelement that reacts to a mouse click
 * each implementation has to be written seperatly
 * when it is clicked it will always set static UIElement::last_clicked_button to its own button type
 */
class UIButton : public UIElement {
public:
    /**
    * @param: quad that defines position and size of the element on screen
    * @param: funct call back function to call when button is clicked
    * @param: parent pointer to the element that contains this element
    */
    UIButton(SDL_Rect quad, UIElement *parent, ButtonTypes button);

    ~UIButton();

    static int mouseClick(void *userdata, SDL_Event *e);

protected:
    //void (*eventhandler)(UIButton &self, SDL_Event &e);
    ButtonTypes button_type;


};

