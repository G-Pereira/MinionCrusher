#include "UIButton.h"

//UIButton::UIButton()
//{
//	rect.x = 0;
//	rect.y = 0;
//	rect.w = 0;
//	rect.h = 0;
//	current = nullptr;
//	mouse_on = nullptr;
//	mouse_off = nullptr;
//	pressed = nullptr;
//}

UIButton::UIButton(SDL_Rect r, SDL_Texture *c, SDL_Texture *on, SDL_Texture *off, SDL_Texture *button_pressed, void funct(UIButton & self, SDL_Event &)):
	rect(r), mouse_on(on), mouse_off(off), pressed(button_pressed), current(c ? c : off), eventhandler(funct){
}

UIButton::~UIButton()
{
}

void UIButton::setPosition(int x, int y)
{
	rect.x = x;
	rect.y = y;
}
void UIButton::setSize(int x, int y)
{
	rect.w = x;
	rect.h = y;
}

void UIButton::handleEvent(SDL_Event* e)
{
	eventhandler(*this, *e);
}
void UIButton::render(SDL_Renderer * renderer)
{
	//Show current button sprite
	SDL_RenderCopy(renderer, current, nullptr, &rect);
}
