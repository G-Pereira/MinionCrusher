#pragma once
#include <string>

#include "SDL.h"

class RenderElement
{
public:
	/**
	 * Overloaded Constructor
	 * @param viewport rectacngle defining the shape and position of the element
	 */
	RenderElement(SDL_Rect viewport, SDL_Renderer * rend, SDL_Texture * text);
	/**
	* overloaded contstructor for when the first UIView, which does not yet have a parent to inherit a renderer from;
	* @param: w width of the element
	* @param: h height of the element
	* @param: rend renderer that goes with the window it is in.
	*/
	RenderElement(SDL_Rect viewport, SDL_Renderer * rend);
	~RenderElement();
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
	 * Render this object
	 */
	virtual void Render();
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
	/**
	* set the rectangle that defines the position and shape of the element
	* @param quad the new quad to use
	*/
	void setQuad(SDL_Rect quad);
	/**
	* get the rectangle that defines the position and shape of the element
	* @return quad of this element
	*/
	SDL_Rect getQuad();
	/**
	* receives SDL_Events
	* @param e SDL_Event
	*/
	virtual void HandleEvents(SDL_Event &e);

	bool hasTexture();
	SDL_Renderer * renderer;
protected:
	SDL_Rect quad;
	SDL_Texture * background;
	void close();
};

