#pragma once

#include "TextureLib.h"

class RenderElement {
public:
    /**
     * Overloaded Constructor
     * @param quad rectacngle defining the shape and position of the element
     */
    RenderElement(SDL_Rect quad, SDL_Texture *text);

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
    virtual void postRender();

    /// Render this object
    virtual void render() = 0;

    /**
     * overloaded Load an image from a link and turn it into a texture with a color key to leave out
     * @param texture pointer to an instantiated texture
     */
    void loadTexture(SDL_Texture *texture);
	/**
	 * create a texture from a string and load it as background
	 * @param path path to the file containing a bitmap
	 */
	void loadText2Texture(std::string text);
    /**
    * set the rectangle that defines the position and shape of the element
    * @param quad the new quad to use
    */
    //void setQuad(SDL_Rect quad);
    /**
    * get the rectangle that defines the position and shape of the element
    * @return quad of this element
    */
    SDL_Rect &getQuad();

    /**
    * check if this object currently has a texture
    * @return true if texture present
    */
    bool hasTexture();

    static SDL_Renderer* renderer;

	static TextureLib* texture_lib;
protected:
    SDL_Rect quad;
    SDL_Texture *background;
};

