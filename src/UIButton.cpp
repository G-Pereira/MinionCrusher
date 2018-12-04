#include "UIButton.h"

UIButton::UIButton(SDL_Rect renderer, SDL_Texture *current, SDL_Texture *mouse_on, SDL_Texture *mouse_off, SDL_Texture *button_pressed, void funct(UIButton & self, SDL_Event &)):
	UIView(renderer), mouse_on(mouse_on), mouse_off(mouse_off), button_pressed(button_pressed), eventhandler(funct){
	background = current ? current : mouse_off;
}

UIButton::~UIButton()
{
}


void UIButton::handleEvent(SDL_Event* e)
{
	eventhandler(*this, *e);
}