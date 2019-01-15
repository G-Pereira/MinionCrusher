/**
 * Base element from which all UIelement inherit. it makes sure the elements can be rendered and passes Events down to its children
 * it also contains some static variables which all of the UI needs to be able to access
 */
#pragma once
#ifndef MINIONCRUSHER_UIVIEW_H
#define MINIONCRUSHER_UIVIEW_H

#include <string>
#include <vector>

#include "RenderElement.h"
#include "gameManager.h"
#include "types.h"

class UIElement : public RenderElement {
public:

    /**
    * overloaded contstructor for when the first UIView, which does not yet have a parent to inherit a renderer from;
    * @param: w width of the element
    * @param: h height of the element
    * @param: parent pointer to the parent UIView of the element
    * @param: rend renderer that goes with the window it is in.
    */
    UIElement(SDL_Rect viewport, UIElement *parent);

    /**
     * Constructor
     * @param w width in pixels
     * @param h height in pixels
     * @param x x position in pixels
     * @param y y position in pixels
     * @param: parent pointer to the parent UIView of the element
     */
    UIElement(int x, int y, int w, int h, UIElement *parent);

    /**
     * Destructor of the UI, calls the UI close method
     */
    virtual ~UIElement();

    /**
     * Render all parts of the user interface
     * @param Map the texture which will be in the background of the map
     * @param info the texture which will be in the background of the info
     * @param buildings the texture which will be in the building buttons
     */
    void render() override;

    /**
     * add to the children of the Element
     * @param new_child UIView element to add to children
     */
    void addChild(UIElement *new_child);

    /**
	 * return the vector of the children
	 * @return a vector with all its children
	 */
    std::vector<UIElement *> getChildren();

    UIElement *getParent();

    void clearChildren();

    static GameManager *gamemanager;

protected:
    std::vector<UIElement *> children;
    UIElement *parent;


    static ButtonTypes last_button_type;

    SDL_Rect nextAutoButtonPosition();

    int button_distance_x = 20;
    int button_distance_y = 20;
    int button_size_x = 100;
    int button_size_y = 100;
private:
};

#endif
