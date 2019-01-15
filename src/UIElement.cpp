#include "UIElement.h"

GameManager *UIElement::gamemanager = nullptr;
ButtonTypes UIElement::last_button_type = ButtonTypes::idle;

UIElement::UIElement(SDL_Rect viewport, UIElement *parent) : RenderElement(viewport), parent(parent) {
    background = nullptr;
}


UIElement::UIElement(int x, int y, int w, int h, UIElement *parent) : UIElement(SDL_Rect{x, y, w, h}, parent) {
}

UIElement::~UIElement() {
    clearChildren();
}


void UIElement::addChild(UIElement *new_child) {
    children.push_back(new_child);
}

std::vector<UIElement *> UIElement::getChildren() {
    return children;
}

UIElement *UIElement::getParent() {
    return parent;
}

void UIElement::clearChildren() {
    for (auto child : children) {
        delete child;
        child = nullptr;
    }
    children.clear();
}

SDL_Rect UIElement::nextAutoButtonPosition() {
    SDL_Rect retquad = SDL_Rect{0};
    if (children.size() == 0) {
        retquad = SDL_Rect{button_distance_x, button_distance_y, button_size_x, button_size_y};
    } else {
        retquad = children.back()->getQuad();
        if (retquad.x + button_distance_x + retquad.w + button_size_x > quad.w) {
            retquad.x = button_distance_x;
            retquad.y += button_distance_y + button_size_y;
            retquad.h = button_size_y;
            retquad.w = button_size_x;
        } else {
            retquad.x += button_distance_x + button_size_x;
            retquad.h = button_size_y;
            retquad.w = button_size_x;
        }
    }
    return retquad;
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
    } else {
        std::cout << quad.x << " " << quad.y << " " << quad.w << " " << quad.h << " no background\n";
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