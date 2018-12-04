#include "UIView.h"


UIView::UIView(SDL_Rect viewport, UIView  *parent, SDL_Renderer * rend):RenderElement(viewport, rend),parent(parent)
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

UIView::UIView(int x, int y, int w, int h, UIView *parent) : UIView(SDL_Rect{ x, y, w,  h }, parent, nullptr)
{
}

UIView::UIView(SDL_Rect viewport, UIView  *parent): UIView(viewport, parent, nullptr)
{
}

UIView::~UIView()
{
	close();
}



void UIView::addChild(UIView * new_child)
{
	children.push_back(new_child);
}

std::vector<UIView*> UIView::getChildren()
{
	return children;
}

void UIView::HandleEvents(SDL_Event & e)
{
	for (UIView* child : children) {
		child->HandleEvents(e);
	}
}

UIView * UIView::getParent()
{
	return parent;
}


void UIView::Render()
{
	preRender();
	//Render texture to screen
	// render children recursively
	//Render texture to screen
	SDL_RenderCopy(renderer, background, nullptr, &quad);

	for (UIView* child : children) {
		SDL_RenderSetViewport(renderer, &quad);
		child->Render();
	}
	postRender();
}