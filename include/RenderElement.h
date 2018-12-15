#pragma once
#include <string>
#include <iostream>

#ifdef _WIN32
#include <SDL.h>
#else

#include "SDL2/SDL.h"

#endif

class RenderElement
{
public:
	/**
	 * Overloaded Constructor
	 * @param quad rectacngle defining the shape and position of the element
	 */
	RenderElement(SDL_Rect quad, SDL_Texture * text);
	/**
	 * overloaded contstructor for when the first UIView, which does not yet have a parent to inherit a renderer from;
	 * @param quad rectacngle defining the shape and position of the element
	 * @param: rend renderer that goes with the window it is in.
	 */
	RenderElement(SDL_Rect quad);
	~RenderElement();
	/**
	 * Render all parts of the user interface
	 * @param Map the texture which will be in the background of the map
	 * @param info the texture which will be in the background of the info
	 * @param buildings the texture which will be in the building buttons
	 */
	virtual void postRender(SDL_Renderer * renderer);
	/**
	 * Render this object
	 */
	virtual void Render(SDL_Renderer * renderer) = 0;
	/**
	 * Load an image from a link and turn it into a texture
	 * @param path path to the file containing a bitmap
	 */
	void loadTexture(SDL_Renderer * renderer, std::string path);
	/**
	 * overloaded Load an image from a link and turn it into a texture with a color key to leave out
	 * @param path path to the file containing a bitmap
	 */
	void loadTexture(SDL_Renderer * renderer, std::string path, SDL_Color color);
	/**
	 * overloaded Load an image from a link and turn it into a texture with a color key to leave out
	 * @param texture pointer to an instantiated texture
	 */
	void loadTexture(SDL_Texture * texture);
	/**
	* set the rectangle that defines the position and shape of the element
	* @param quad the new quad to use
	*/
	//void setQuad(SDL_Rect quad);
	/**
	* get the rectangle that defines the position and shape of the element
	* @return quad of this element
	*/
	SDL_Rect& getQuad();

	bool hasTexture();
	//SDL_Renderer * renderer;
protected:
	SDL_Rect quad;
	SDL_Texture * background;
};

