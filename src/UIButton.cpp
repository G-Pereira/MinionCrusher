#include "UIButton.h"

UIButton::UIButton(SDL_Rect quad, void funct(UIButton & self, SDL_Event &), UIView * parent):
	UIView(quad, parent), eventhandler(funct){
}

UIButton::~UIButton() {
}


void UIButton::handleEvents(SDL_Event* e)
{
	std::cout << "UIButton SDL_event\n";
	if(eventhandler)
		eventhandler(*this, *e);
}