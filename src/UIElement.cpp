#include "UIElement.h"


UIElement::UIElement(SDL_Rect viewport, UIElement  *parent):RenderElement(viewport),parent(parent)
{
	background = nullptr;
}


UIElement::UIElement(int x, int y, int w, int h, UIElement * parent) : UIElement(SDL_Rect{x,y,w,h}, parent)
{
}

UIElement::~UIElement()
{
	close();
}



void UIElement::addChild(UIElement * new_child)
{
	children.push_back(new_child);
}

std::vector<UIElement*> UIElement::getChildren()
{
	return children;
}

void UIElement::HandleEvents(SDL_Event & e)
{
	for (UIElement* child : children) {
		child->HandleEvents(e);
	}
}

UIElement * UIElement::getParent()
{
	return parent;
}


void UIElement::Render(SDL_Renderer * renderer)
{
	if (!renderer) {
		std::cout << "no renderer in UIElement\n";
		return;
	}

	preRender(renderer);
	// Render texture to screen
	// render children recursively
	if(background)
		SDL_RenderCopy(renderer, background, nullptr, &quad);

	for (UIElement* child : children) {
		SDL_RenderSetViewport(renderer, &quad);
		child->Render(renderer);
	}
	postRender(renderer);
}