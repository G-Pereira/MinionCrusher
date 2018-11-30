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

UIButton::UIButton(SDL_Rect r, SDL_Texture *c, SDL_Texture *on, SDL_Texture *off, SDL_Texture *button_pressed)
{
	rect = r;
	mouse_on = on;
	mouse_off = off;
	pressed = button_pressed;
	current = mouse_off;
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
	//If mouse event happened
	if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP)
	{
		//Get mouse position
		int x, y;
		SDL_GetMouseState(&x, &y);

		//Check if mouse is in button
		bool inside = true;

		//Mouse is left of the button
		if (x < rect.x)
		{
			inside = false;
		}
		//Mouse is right of the button
		else if (x > rect.x + rect.w)
		{
			inside = false;
		}
		//Mouse above the button
		else if (y < rect.y)
		{
			inside = false;
		}
		//Mouse below the button
		else if (y > rect.y + rect.h)
		{
			inside = false;
		}

		//Mouse is outside button
		if (!inside)
		{
			current = mouse_off;
		}
		//Mouse is inside button
		else
		{
			//Set mouse over sprite
			switch (e->type)
			{
			case SDL_MOUSEMOTION:
				current = mouse_on;
				break;

			case SDL_MOUSEBUTTONDOWN:
				current = pressed;
				break;

			case SDL_MOUSEBUTTONUP:
				current = pressed;
				break;
			}
		}
	}
}
void UIButton::render(SDL_Renderer * renderer)
{
	//Show current button sprite
	SDL_RenderCopy(renderer, current, nullptr, &rect);
}
