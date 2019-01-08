#include "UIElement.h"

GameManager  * UIElement::gamemanager = nullptr;

UIElement::UIElement(SDL_Rect viewport, UIElement *parent) : RenderElement(viewport), parent(parent) {
    background = nullptr;
}


UIElement::UIElement(int x, int y, int w, int h, UIElement *parent) : UIElement(SDL_Rect{x, y, w, h}, parent) {
}

UIElement::~UIElement() {
    // Delete all childs that have been allocated on the heap
    for (UIElement *child : children) {
        delete child;
    }
}


void UIElement::addChild(UIElement *new_child) {
    children.push_back(new_child);
}

std::vector<UIElement *> UIElement::getChildren() {
    return children;
}

void UIElement::handleEvents(SDL_Event &e) {
    for (UIElement *child : children) {
        child->handleEvents(e);
    }
}

UIElement *UIElement::getParent() {
    return parent;
}


void UIElement::render() {
    if (RenderElement::renderer == nullptr) {
        std::cout << "SDL_Renderer not found!\n";
        return;
    }

    // render texture to screen
    if (background != nullptr) {
        //std::cout << "Rendering background" << std::endl;
        SDL_RenderCopy(RenderElement::renderer, background, nullptr, &quad);
	}
	else {
		std::cout << quad.x << " " << quad.y << " " << quad.w << " " << quad.h <<  " no background\n" ;
	}

	// render children recursively
    if (children.size() > 0 && quad.h > 0 && quad.w > 0) {
        for (UIElement *child : children) {
            SDL_RenderSetViewport(RenderElement::renderer, &quad);
            child->render();
        }
    }
    postRender();
}