#include "UIButton.h"

UIButton::UIButton(SDL_Rect quad, UIElement *parent, SDL_EventFilter filter) :
        UIElement(quad, parent), filter(filter) {
	SDL_AddEventWatch(mouseClick, this);
}

UIButton::~UIButton() {
}


void UIButton::handleEvents(SDL_Event &e) {
    if (filter)
        filter(nullptr, &e);
}

int UIButton::mouseClick(void * userdata, SDL_Event * e)
{
	if (userdata == nullptr) {
		throw;
		return 0;
	}
	UIButton * clicked_button = reinterpret_cast<UIButton *>(userdata);
	//If mouse event happened
	if (e->type == SDL_MOUSEBUTTONDOWN) {
		//Get mouse position
		int x = e->button.x;
		int y = e->button.y;
		//SDL_GetMouseState(&x, &y);
		// go through this object and all parents to substracct the total offset
		UIElement *UI_elem = clicked_button;
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
		else if (x > clicked_button->quad.w) {
			inside = false;
		}
		//Mouse above the button
		else if (y < 0) {
			inside = false;
		}
		//Mouse below the button
		else if (y > clicked_button->quad.h) {
			inside = false;
		}

		//Mouse is outside button
		if (!inside) {
			// do nothing
		}
		//Mouse is inside button
		else {
			if (clicked_button->filter)
				clicked_button->filter(nullptr, e);
		}
	}
	return 0;
}
