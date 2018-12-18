#include "BuildButton.h"

int OnMouseClick(void* data, SDL_Event * e) {
	BuildButton * button = (BuildButton *)data;
	button->handleEvents(*e);
	return 0;
}
BuildButton::BuildButton(SDL_Rect quad, void funct(UIButton &self, SDL_Event &), UIElement *parent)
        : UIButton(quad, funct, parent) {
	
	SDL_AddEventWatch(OnMouseClick,this);
}

void BuildButton::handleEvents(SDL_Event &e) {
    //If mouse event happened
    if (e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP) {
        //Get mouse position
        int x, y;
        SDL_GetMouseState(&x, &y);
        //std::cout << "mouse event; mouse state:" << x << ", " << y << std::endl;
        // add the offset of the viewport
        x -= quad.x;
        y -= quad.y;
        //std::cout << "after quad substraction :" << x << ", " << y << std::endl;
        // go through all parents to substracct the total offset
        UIElement *UI_elem = getParent();
        while (UI_elem) {
            x -= UI_elem->getQuad().x;
            y -= UI_elem->getQuad().y;
            UI_elem = UI_elem->getParent();
        }
        //std::cout << "after tree calculation:" << x << ", " << y << std::endl;
        //Check if mouse is in button
        bool inside = true;

        //Mouse is left of the button
        if (x < 0) {
            inside = false;
        }
            //Mouse is right of the button
        else if (x > quad.w) {
            inside = false;
        }
            //Mouse above the button
        else if (y < 0) {
            inside = false;
        }
            //Mouse below the button
        else if (y > quad.h) {
            inside = false;
        }

        //Mouse is outside button
        if (!inside) {
            // do nothing
        }
            //Mouse is inside button
        else {
            //Set mouse over sprite
            switch (e.type) {
                case SDL_MOUSEMOTION:
                    //cout << "SDL_MOUSEMOTION" << endl;
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    if (eventhandler)
                        eventhandler(*this, e);
                    std::cout << "BuildButton SDL_MOUSEBUTTONDOWN" << std::endl;
                    break;

                case SDL_MOUSEBUTTONUP:
                    //std::cout << "SDL_MOUSEBUTTONUP" << std::endl;
                    break;
            }
        }
    }
}
