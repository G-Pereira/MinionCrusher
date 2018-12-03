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

UIButton::UIButton(SDL_Rect renderer, SDL_Texture *current, SDL_Texture *mouse_on, SDL_Texture *mouse_off, SDL_Texture *button_pressed, void funct(UIButton & self, SDL_Event &)):
	rect(renderer), current(current ? current : mouse_off), mouse_on(mouse_on), mouse_off(mouse_off), button_pressed(button_pressed), eventhandler(funct){
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
