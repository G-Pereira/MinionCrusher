#include "UIElement.h"


UIElement::UIElement(SDL_Rect viewport, UIElement  *parent, SDL_Renderer * rend):RenderElement(rend, viewport),parent(parent)
{
	//if no renderer is created try to inherit from parent
	if (!renderer) {
		try {
			renderer = parent->renderer;
		}
		catch (std::exception& e) {
			std::cout << "first UIView must be initialized with a renderer\n";
			std::cout << e.what();
		}
	}
	background = nullptr;
}

UIElement::UIElement(int x, int y, int w, int h, UIElement *parent) : UIElement(SDL_Rect{ x, y, w,  h }, parent, nullptr)
{
}

UIElement::UIElement(SDL_Rect viewport, UIElement  *parent): UIElement(viewport, parent, nullptr)
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


void UIElement::Render()
{
	preRender();
	//Render texture to screen
	// render children recursively
	//Render texture to screen
	SDL_RenderCopy(renderer, background, nullptr, &quad);

	for (UIElement* child : children) {
		SDL_RenderSetViewport(renderer, &quad);
		child->Render();
	}
	postRender();
}