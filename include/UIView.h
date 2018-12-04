/**
* Base element from which all UIelement inherit. it makes sure the elements can be rendered and passes Events down to its children
*/
#pragma once
#ifndef MINIONCRUSHER_UIVIEW_H
#define MINIONCRUSHER_UIVIEW_H

#include <SDL.h>
#include <string>
#include <vector>
#include "MapObject.h"
#include <vector>
#include "Map.h"


class UIView {
public:

	/**
	* overloaded contstructor for when the first UIView, which does not yet have a parent to inherit a renderer from;
	* @param: w width of the element
	* @param: h height of the element
	* @param: parent pointer to the parent UIView of the element
	* @param: rend renderer that goes with the window it is in.
	*/
	UIView(SDL_Rect viewport, UIView  *parent, SDL_Renderer * rend);
	/**
	 * Overloaded Constructor
	 * @param viewport rectacngle defining the shape and position of the element
	 * @param: parent pointer to the parent UIView of the element
	 */
	UIView(SDL_Rect viewport, UIView * parent);
	/**
	 * Constructor
	 * @param w width in pixels
	 * @param h height in pixels
	 * @param x x position in pixels
	 * @param y y position in pixels
	* @param: parent pointer to the parent UIView of the element
	 */
	UIView(int x, int y, int w, int h, UIView * parent);

	/**
	 * Destructor of the UI, calls the UI close method
	 */
	~UIView();
	/**
	 * Initilialize the UI
	 */
	void init();
	/**
	 * Render all parts of the user interface
	 * @param Map the texture which will be in the background of the map
	 * @param info the texture which will be in the background of the info
	 * @param buildings the texture which will be in the building buttons
	 */
	virtual void preRender();
	/**
	 * Render all parts of the user interface
	 * @param Map the texture which will be in the background of the map
	 * @param info the texture which will be in the background of the info
	 * @param buildings the texture which will be in the building buttons
	 */
	virtual void postRender();
	/**
	 * Render all parts of the user interface
	 * @param Map the texture which will be in the background of the map
	 * @param info the texture which will be in the background of the info
	 * @param buildings the texture which will be in the building buttons
	 */
	void Render();
	/**
	 * returns a pointer to the renderer
	 * @return pointer to the used renderer
	 */
	SDL_Renderer *getRenderer() const;
	/**
	 * Load an image from a link and turn it into a texture
	 * @param path path to the file containing a bitmap
	 * @return pointer to texture
	 */
	void loadTexture(std::string path);

	void setQuad(SDL_Rect);
	void addChild(UIView * new_child);
	std::vector<UIView*> getChildren();

	virtual void HandleEvents(SDL_Event &e);

	void close();

	SDL_Texture * background;
	SDL_Renderer * renderer;
	SDL_Rect quad;
	std::vector<UIView*> children;
	UIView * parent;
};






#endif
