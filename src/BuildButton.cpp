#include "BuildButton.h"

int buildTowerOnMapClick(void* data, SDL_Event * e) {
	((BuildButton *)data)->gamemanager->map->towers.emplace_back(2, 5, 1, 1, 25, 3, 10, AmmoType{});
	SDL_DelEventWatch(buildTowerOnMapClick, data);
	return 0;
}

BuildButton::BuildButton(SDL_Rect quad, void funct(UIButton &self, SDL_Event &), UIElement *parent)
        : UIButton(quad, funct, parent) {
	
	//SDL_AddEventWatch(BuildButton::OnMouseClick,this);
}

void BuildButton::handleEvents(SDL_Event &e) {
    //If mouse event happened
    if (e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP) {
        //Get mouse position
		int x = e.button.x;
		int y = e.button.y;
        //SDL_GetMouseState(&x, &y);
        // go through this object and all parents to substracct the total offset
		UIElement *UI_elem = this;
        while (UI_elem) {
            x -= UI_elem->getQuad().x;
            y -= UI_elem->getQuad().y;
            UI_elem = UI_elem->getParent();
        }
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
            switch (e.type) {
                case SDL_MOUSEMOTION:
                    //cout << "SDL_MOUSEMOTION" << endl;
                    break;

                case SDL_MOUSEBUTTONDOWN:
                   /* if (filter)
						filter(*this, e);*/
                    std::cout << "BuildButton SDL_MOUSEBUTTONDOWN" << std::endl;
					SDL_AddEventWatch(buildTowerOnMapClick, this);
                    break;

                case SDL_MOUSEBUTTONUP:
                    //std::cout << "SDL_MOUSEBUTTONUP" << std::endl;
                    break;
            }
        }
    }
}
